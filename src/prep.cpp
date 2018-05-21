#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include "../include/prep.hpp"
// #include "../include/lexer.hpp"

bool read_source_line(std::string line, vector_of_tokens* Tokens, int *linha){
    if (line.empty())   return false;
    Token_str Token;
    while (line[0] == ' ') line.erase(0,1); // Trim Spaces
    if    (line.size() == 1){
        *linha= *linha+1;
        return false;
    }    
    if    (line[0] == ';') return false;  // Ignore Comments
    std::string buf;            // Have a buffer std::string
    std::stringstream ss(line); // Insert the std::string into a stream

    while (ss  >> buf){
        std::transform(buf.begin(), buf.end(),buf.begin(), ::toupper);
        if (buf.compare(0,1,";")==0){
            break;
        }
        Token.token_string = buf;
        Token.token_line = *linha;
        Tokens->push_back(Token);
    }
    *linha=*linha+1;
    return true;
}

bool treating_if(vector_of_tokens* Tokens){
    std::string label;
    int ifzero = 0;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (it->label_equ == true){
            for (vector_of_tokens::iterator it_2 = it ; it_2 != Tokens->end(); ++it_2){
                label = it->token_string;
                label.erase(label.size()-1,1);
                if(it_2->token_string.compare(label) == 0){
                    it_2->token_string = (it+2)->token_string;
               } 
            }
            Tokens->erase(it);
            Tokens->erase(it);
            Tokens->erase(it);
            it=it-1;

        }
    }

    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (it->token_string.compare("IF") == 0){
            if ((it+1) != Tokens->end()){
                if ((it+1)->token_string.compare("1") == 0){
                  Tokens->erase(it);
                  Tokens->erase(it);
                  it = it-1;  
                }
                else{
                    if((it+2) != Tokens->end()){
                        ifzero = (it+2)->token_line;
                        while((it+2) != Tokens->end() && ((it+2)->token_line)==ifzero){
                            Tokens->erase(it+2);   
                        }
                    }
                Tokens->erase(it);
                Tokens->erase(it);
                }

            }
        }

    }

    return true;
}


void update_label_flags(vector_of_tokens* Tokens){
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if((it+1) != Tokens->end()){
            if (it->token_string.compare(((it->token_string.size())-1),1,":") == 0){
              if((it+1)->token_string.compare("EQU") == 0){
                it->label_equ = true;
              }
              else if((it+1)->token_string.compare("MACRO") == 0){
                it->label_macro = true;
              }
              else{
                it->label = true;
              } 
            }
        }
    }
}

void label_tokens(vector_of_tokens* Tokens){
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if(it->token_string.compare(0,1,":") == 0){
            Tokens->erase(it);
            (it-1)->token_string =(it-1)->token_string +':';
        }
    }
}

void if_equ_output(vector_of_tokens* Tokens,source* output,bool macros){
    int linha = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (linha != it->token_line){
            if(!macros){
                output->push_back("\n");
            }
            linha= it->token_line;
        }
        if(!macros){
            output->push_back(it->token_string + " ");
        }
    }
}

void separe_copy_tokens(vector_of_tokens *Tokens){
    bool Flag_copy = false;
    Token_str Token;
    int linha = 0;
    std::string temp_str;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if(Flag_copy == true){//separe where are commas into differents tokens
            std::stringstream temp((it)->token_string);
            linha = (it->token_line);
            it = Tokens->erase(it);
            while( temp.good() ){
            std::getline( temp, temp_str, ',' );
            Token.token_string = temp_str;
            Token.token_line = linha;
            (it) = Tokens->insert(it,Token);
            it++;
            }
            Flag_copy = false;
        }
        if (it->token_string.compare("COPY") == 0){
            Flag_copy = true;//set flag to true to separe tokens with commas
        }
    }
}
void separe_macro_tokens(vector_of_tokens *Tokens){
   bool Flag_macro = false;
    Token_str Token;
    int linha = 0;
    std::string temp_str;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if(Flag_macro == true){//separe where are commas into differents tokens
            std::stringstream temp((it)->token_string);
            linha = (it->token_line);
            it = Tokens->erase(it);
            while( temp.good() ){
            std::getline( temp, temp_str, ',' );
            Token.token_string = temp_str;
            Token.token_line = linha;
            (it) = Tokens->insert(it,Token);
            it++;
            }
            Flag_macro = false;
        }
        if (it->token_string.compare("MACRO") == 0){
            Flag_macro = true;//set flag to true to separe tokens with commas
        }
    } 
}

bool treating_macro(vector_of_tokens* Tokens){
    vector_of_tokens  DEF;
    std::string temp;
    std::map<std::string,int> MNT;
    std::map<std::string,vector_of_tokens> M_DEF;
    DEF.clear();
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if(it->label_macro == true){
            temp = it->token_string;
            temp.pop_back();
            MNT.insert(std::pair<std::string,int>(temp,1));
        }
    }//making MNT
    #ifdef DEBUG_MDT_MNT
    std::cout << "MNT contains:\n";
    for (std::map<std::string,int>::iterator it = MNT.begin(); it!=MNT.end(); ++it){
        std::cout << it->first << " => " << it->second << '\n';
    }//printing MNT
    #endif
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if(it->label_macro == true){
            temp = it->token_string;
            temp.pop_back();
            Tokens->erase(it);
            // it++;
            while(it->token_string.compare("ENDMACRO")!=0){
                DEF.push_back(*it);
                Tokens->erase(it);    
            }
            DEF.push_back(*it);
            Tokens->erase(it);
            it--;
            M_DEF.insert(std::pair<std::string,vector_of_tokens>(temp,DEF));
        }
        DEF.clear();
    }//making MDT = M_DEF
    #ifdef DEBUG_MDT_MNT
    std::cout<<std::endl << "MDT contains:\n";
    for (std::map<std::string,vector_of_tokens>::iterator it = M_DEF.begin(); it!=M_DEF.end(); ++it){
        std::cout << it->first << " => ";
        int line = it->second.begin()->token_line;
        for (vector_of_tokens::iterator it_2 = it->second.begin() ; it_2 != it->second.end(); ++it_2){
            if (line != it_2->token_line){
                std::cout << '\n';
                line= it_2->token_line;
            }
            std::cout << it_2->token_string<<'('<<it_2->token_line<<')'<<'|';
        }
        std::cout << '\n';
    }
    std::cout<<"\nMACROS OF MDT ENDS HERE\n";
    #endif
    return true;
}

void preprocess(source& file, source* output, bool macros,vector_of_tokens* Tokens){
    if(file.empty()) return;
    int linha = 1;
    foreach(i, file){
        read_source_line(file[i],Tokens,&linha);//make the vector of tokens
        #ifdef DEBUG_PREP_INPUT
            std::cout << file[i] << std::endl;
        #endif // DEBUG_PREP_OUTPUT
    }

    label_tokens(Tokens);// if there is a token ':', put : in the final of previous token
    update_label_flags(Tokens);// update label Flags

    #ifdef DEBUG_PREP_PRINT_TOKENS
    int line = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (line != it->token_line){
            std::cout << '\n';
            line= it->token_line;
        }
        std::cout << it->token_string<<'('<<it->token_line<<')'<<' '
        <<"eq"<<it->label_equ<<"mac"<<it->label_macro<<"label"
        <<it->label<<" ";
    }
    std::cout << '\n';
    #endif

    treating_if(Tokens);//treating IF EQU clauses

    #ifdef DEBUG_PREP_OUTPUT
    linha = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (linha != it->token_line){
            std::cout << '\n';
            linha= it->token_line;
        }
        std::cout << it->token_string<<' ';
    } 
    #endif
    if(!macros){
        if_equ_output(Tokens,output,macros);//make the outputfile when -p
        return ; 
    }
           
//here ends -p input, for now on is macros working


    #ifdef DEBUG_MAC_TOKENS_FLAGS
    int line = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (line != it->token_line){
            std::cout << '\n';
            line= it->token_line;
        }
        std::cout << it->token_string<<'('<<it->token_line<<')'<<' '
        <<"m"<<it->label_macro<<"l"
        <<it->label<<" ";
    }
    std::cout << '\n';
    #endif

    separe_copy_tokens(Tokens);
    // separe_macro_tokens(Tokens);
    #ifdef DEBUG_MAC_PRINT_TOKENS_IN
    std::cout<<"\033[04;32m"<<"\nPRINTS OUTPUT TOKENS BEFORE MACROS WORKS\n\n"<<"\033[00m";
    int line = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (line != it->token_line){
            std::cout << '\n';
            line= it->token_line;
        }
        std::cout << it->token_string<<'('<<it->token_line<<')'<<it->qnt_mac_param<<'|';
    }
    std::cout << '\n';
    #endif

    treating_macro(Tokens);

    #ifdef DEBUG_MAC_PRINT_TOKENS_OUT
    std::cout<<"\033[04;32m"<<"\nPRINTS OUTPUT TOKENS AFTER MACROS WORKS\n\n"<<"\033[00m";
    int line = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (line != it->token_line){
            std::cout << '\n';
            line= it->token_line;
        }
        std::cout << it->token_string<<'('<<it->token_line<<')'<<it->qnt_mac_param<<'|';
    }
    std::cout << '\n';
    #endif


}

