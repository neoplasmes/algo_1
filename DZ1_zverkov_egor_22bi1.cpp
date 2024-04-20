#include <iostream>
#include <vector>
#include <cinttypes>

using namespace std;

int objects = 0;


class binaryNumber{
    private:
        const int8_t maxSize = 8; 
        int8_t* value;


        //складывает два чилса и возвращает новое
        binaryNumber summator(binaryNumber& arg1, binaryNumber& arg2){
            binaryNumber result;

            int8_t temp = 0;
            for (int8_t i = maxSize - 1; i >= 0; i--) {
                int8_t bitSum = arg1[i] + arg2[i] + temp;
                result[i] = bitSum % 2;
                temp = bitSum / 2;
            }

            //cout << (int)temp << endl;
            return result;
        }

        void adder(const binaryNumber& other){
            int8_t temp = 0;
            for (int8_t i = maxSize - 1; i >= 0; i--) {
                int8_t bitSum = this->value[i] + other.value[i] + temp;
                this->value[i] = bitSum % 2;
                temp = bitSum / 2;
            }
            //cout << (int)temp << endl;
        }

        //увеличить на один
        void incrementor(binaryNumber& arg1) {
            int8_t temp = 1;
            for (int8_t i = maxSize - 1; i >= 1; i--){
                int8_t bitSum = arg1[i] + temp;
                arg1[i] = bitSum % 2;
                temp = bitSum / 2;
                if (temp == 0) {
                    break;
                }
            }
        }

        //инертировать
        void invertor(binaryNumber& arg){
            for (int8_t i = 0; i < maxSize; i++){
                arg[i] = !arg[i];
            }
        }

        void shiftLeft(binaryNumber& arg){
            for (int8_t i = maxSize - 1; i >= 1; i--) {
                arg[i-1] = arg[i];
            }
            arg[maxSize-1] = 0;
        }        

    public:
        //дефолтный инициализатор, все нули
        binaryNumber(){
            objects++;

            value = new int8_t[maxSize];
            for (int8_t i = 0; i < maxSize; i++) {
                value[i] = 0;
            }
        }

        //конструктор с десятичным числом-инициализатором
        binaryNumber(int n){
            objects++;

            if (n > 127 || n < -127){
                throw invalid_argument("initializator is out of range");
            }   
            int8_t at = maxSize - 1;
            value = new int8_t[maxSize];
            if(n >= 0){
                value[0] = 0;

                while(n >= 1){
                    value[at--] = n % 2;
                    n = n / 2;
                }

                for (int8_t i = 1; i <= at; i++) {
                    value[i] = 0;
                }
            } else {
                value[0] = 1;
                n = 0 - n - 1;

                while(n >= 1){
                    value[at--] = !(n % 2);
                    n = n / 2;
                }

                for (int8_t i = 1; i <= at; i++) {
                    value[i] = 1;
                }
            }         
        }


        binaryNumber& operator=(binaryNumber& other){
            for (int8_t i = 0; i < maxSize; i++){
                value[i] = other[i];
            }

            return (*this);
        }

        binaryNumber& operator+=(const binaryNumber& other){
            adder(other);
            return (*this);
        }

        binaryNumber operator+(binaryNumber& other){
            return summator((*this), other);
        }  

        binaryNumber operator-(binaryNumber& other){
            invertor(other);
            incrementor(other);
            return summator((*this), other);
        }      

        binaryNumber operator*(binaryNumber& other){
            binaryNumber result;
            binaryNumber temp = (*this);

            //result[0] = (value[0] != number[0]);

            for (int8_t i = maxSize - 1; i >= 0; i--){
                if (other[i] == 1){
                    result += temp;
                    //cout << result.getBinaryValue() << endl;
                }
                
                shiftLeft(temp);
            }

            return result;
        }

        int8_t& operator[](size_t i){
            return value[i];
        }

        string getBinaryValue(){
            string s = "";
            for (int8_t i = 0; i < maxSize; i++){
                s = s + to_string(value[i]);
            }

            return s;
        }

        ~binaryNumber(){
            objects--;
            /*cout << "destruct" << endl;*/
            delete[] value;
        }
};






int main(){
    binaryNumber a(5);
    binaryNumber b(10);

    cout << endl;
    cout << (a * b).getBinaryValue();

    return 0;
}   