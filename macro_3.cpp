#include<bits/stdc++.h>
using namespace std;

#define endl '\n'

struct macro_def{
    string macro_name;
    vector<string> para_list;
    vector<string> definition;
};

std::vector<std::string> extractWords(const std::string& input) {
    std::vector<std::string> words;
    std::istringstream iss(input);

    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}

//to join string with punctuator
string join_str(vector<string> &arr,string p){
    string ans;
    for(auto it:arr){
        if(ans.size()!=0){
            ans+=p;
        }
        ans+=it;
    }
    return ans;
}

// Function to tokenize a string
std::vector<std::string> tokenize(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        // if(token==" "){
        //     continue;
        // }
        tokens.push_back(token);
        // cout<<token<<endl;
    }

    return tokens;
}

//to read the macro definition
void firstpass(map<string,macro_def *> &m,string input_file){
    ifstream in(input_file);
    string line;
    // int count=0;
    while(getline(in,line)){
        // cout<<count<<endl;
        // count++;
        vector<string> words=extractWords(line);
        if(words.size()>2&&words[1]=="macro"){
            macro_def *new_macro=new macro_def;
            new_macro->macro_name=words[0];
            int n=words.size();
            //getting the macro paramenter
            for(int i=2;i<n;i++){
                new_macro->para_list.push_back(words[i]);
            }
            string def_line;
            while(getline(in,def_line)){
                vector<string> def_words=extractWords(def_line);
                if(def_words[0]=="endm"){
                    break;
                }
                else{
                    new_macro->definition.push_back(def_line);
                }
            }
            m[new_macro->macro_name]=new_macro;
        }
    }
    in.close();
}

//to replace the macro 
void secondpass(map<string,macro_def *> &m,string input_file,string output_file){
    ofstream out(output_file);
    ifstream in(input_file);
    string line;
    while(getline(in,line)){
        vector<string> words=extractWords(line);
        if(words.size()>0&&m.count(words[0])){
            map<string,string> arg_list;
            if(words.size()>1&&words[1]=="macro"){
                out<<line<<endl;
                continue;
            }
            string space;
            int str_len=line.size();
            int j=0;
            while(j<str_len&&(line[j]==' '||line[j]=='\t')){
                space.push_back(line[j++]);
            }
            int n=words.size();
            macro_def* macro=m[words[0]];
            // cout<<n<<" "<<macro->para_list.size()<<endl;
            // for(auto it:words){
            //     cout<<it<<" ";
            // }
            // cout<<endl;
            if((n-1)!=macro->para_list.size()){
                cout<<"Parameter list doesn't match"<<endl;
                exit(1);
            }
            int i=1;
            //formal and actual parameter mapping
            for(auto it:macro->para_list){
                arg_list[it]=words[i++];
            }
            //replace the macro with macro definition
            for(auto def_line:macro->definition){
                vector<string> def_words=extractWords(def_line);
                int n=def_words.size();
                for(int i=0;i<n;i++){
                    if(arg_list.count(def_words[i])){
                        def_words[i]=arg_list[def_words[i]];
                    }
                }
                string final_line=join_str(def_words," ");
                // string space;
                // int i=0;
                // int line_len=line.size();
                // while(i<line_len&&line[i]==' '){
                //     space+=" ";
                //     i++;
                // }
                out<<space<<final_line<<endl;
            }
        }
        else{
            out<<line<<endl;
        }
    }

    in.close();
    out.close();
}

int main(){
    string input_file="input1.asm";
    string output_file="output_1.txt";
    ofstream out(output_file);
    map<string,macro_def*> m;
    firstpass(m,input_file);
    // cout<<"hello world"<<endl;
    // cout<<m.size()<<endl;


    //to write the macro definition 
    // for(auto it:m){
    //     macro_def *macro=it.second;
    //     out<<""<<macro->macro_name<<" macro";
    //     for(auto it:macro->para_list){
    //         out<<" "<<it;
    //     }
    //     out<<endl;
    //     for(auto it:macro->definition){
    //         out<<it<<endl;
    //     }
    // }


    secondpass(m,input_file,output_file);

    return 0;
}