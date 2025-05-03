
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

string codeName(string str1, string str2){
    string code;
    for (int i =0; i < str1.length(); i++){
        if (str1[i]>='A' && str1[i]<='Z'){
            code+=str1[i]+32; //decimal difference between capital and corresponding lowercase letter
        }
        else if (str1[i] == ' '){
            continue;
        }
        else{
            code+= str1[i];
        }
    }
    for (int i =0; i < str2.length(); i++){
        if (str2[i]>='A' && str2[i]<='Z'){
            code+= str2[i] + 32; //decimal difference between capital and corresponding lowercase letter
        }
        else if (str2[i] == ' '){
            continue;
        }
        else{
            code+= str2[i];
        }
    }
    return code;
}
