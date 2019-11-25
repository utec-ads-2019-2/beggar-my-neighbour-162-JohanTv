#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

vector<string> Dealer;
vector<string> User;
vector<string> mid;

string card;
int num;
bool turn = true;
bool exito = true;
bool turnPlayer(){
    if (turn){
        if(User.size()>0){
            card = User.front();
            User.erase(User.begin());
        }
        else return false;
    }
    else{
        if(Dealer.size()>0){
            card = Dealer.front();
            Dealer.erase(Dealer.begin());
        }
        else return false;
    }
    mid.push_back(card);
    return true;
}

bool isFaceCard(string& check){
    switch(check[1]){
        case 'A': {
            num = 4; break;
        }
        case 'J': {
            num = 1; break;
        }
        case 'Q': {
            num = 2; break;
        }
        case 'K': {
            num = 3; break;
        }
        default : num = 0;
    }
    return num != 0;
}

void battle(int count){
    bool good;
    while(count > 0){
        good = turnPlayer();
        if(good){
            if(isFaceCard(mid.back())){
                break;
            }
            count--;
        }
        else break;
    }

    if(count != 0) {
        if(good){
            turn = !turn;
            battle(num);
        }
        else exito = good;
    }else{
        if(!turn){
            User.insert(User.end(),mid.begin(),mid.end());
            mid.clear();
        }
        else{
            Dealer.insert(Dealer.end(),mid.begin(),mid.end());
            mid.clear();
        }
    }
}
void start(){
    while(exito){
        exito = turnPlayer();
        if(exito){
            if(isFaceCard(mid.back())){
                turn = !turn;
                battle(num);
                turn = !turn;
            }
            else{
                turn = !turn;
            }
        }
    }
}

bool decksOfCards() {
    cin>>card;
    if(card != "#"){
        User.insert(User.begin(),card);

        int numCards = 2;
        while(numCards <= 52) {
            if (numCards % 2 == 0) {
                cin >> card;
                Dealer.insert(Dealer.begin(),card);
            } else {
                cin >> card;
                User.insert(User.begin(),card);
            }
            numCards++;
        }
        return true;
    }
    return false;

}

int main() {
    while(decksOfCards()){
        start();
        if(User.size() != 0){
            cout<<2<<setw(3)<<User.size()<<endl;
        }
        else{
            cout<<1<<setw(3)<<Dealer.size()<<endl;
        }
        Dealer.clear();
        User.clear();
        mid.clear();
        exito = true;
        turn = true;
    }
    return 0;
}
