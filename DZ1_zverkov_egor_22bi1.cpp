#include <iostream>
#include <math.h>

using namespace std;

int objects = 0;

const int maxSize = 8;
int positiveLimit = pow(2, maxSize-1) - 1;
int negativeLimit = 0 - positiveLimit - 1;

class binaryNumber {
    private:
        int* value;


        //складывает два чилса и возвращает новое
        binaryNumber summator(const binaryNumber& arg1, const binaryNumber& arg2) {
            binaryNumber result;
            int initialSignLeft = arg1.value[0];
            int initialSignRight = arg2.value[0];

            int temp = 0;
            for (int i = maxSize - 1; i >= 0; i--) {
                int bitSum = arg1.value[i] + arg2.value[i] + temp;
                result.value[i] = bitSum % 2;
                temp = bitSum / 2;
            }

            int finalSign = result.value[0];

            //оба знака должны быть равны финальному
            if ((initialSignLeft != finalSign) && (initialSignRight != finalSign)) {
                throw overflow_error("переполнение при вычислении, введите другие аргументы");
            }
            //cout << (int)temp << endl;
            return result;
            
        }

        //
        void adder(const binaryNumber& other) {
            int initialSignLeft = this->value[0];
            int initialSignRight = other.value[0];

            int temp = 0;
            for (int i = maxSize - 1; i >= 0; i--) {
                int bitSum = this->value[i] + other.value[i] + temp;
                this->value[i] = bitSum % 2;
                temp = bitSum / 2;
            }

            int finalSign = this->value[0];
            if ((initialSignLeft != finalSign) && (initialSignRight != finalSign)) {
                throw overflow_error("переполнение при вычислении, введите другие аргументы");
            }
        }

        //увеличить на один
        void incrementor() {
            
            int initialSign = value[0];
            int temp = 1;
            for (int i = maxSize - 1; i >= 1; i--) {
                int bitSum = value[i] + temp;
                value[i] = bitSum % 2;
                temp = bitSum / 2;
                if (temp == 0) {
                    break;
                }
            }
            int finalSign = value[0];
            if (initialSign != finalSign) {
                throw overflow_error("переполнение при вычислении, введите другие аргументы");
            }           
        }

        //инертировать
        void invertor() {
            for (int i = 0; i < maxSize; i++) {
                value[i] = !value[i];
            }
        }

        void shiftLeft() {
            for (int i = 0; i < maxSize - 1; i++) {
                value[i] = value[i + 1];
            }
            value[maxSize - 1] = 0;
        }

    public:
        //дефолтный конструктор, все нули
        binaryNumber() {
            objects++;

            value = new int[maxSize];
            for (int i = 0; i < maxSize; i++) {
                value[i] = 0;
            }
        }

        //конструктор копия без которой не работает равно
        binaryNumber(const binaryNumber& other) {
            objects++;

            this->value = new int[maxSize];
            for (int i = 0; i < maxSize; i++) {
                this->value[i] = other.value[i];
            }
        }

        //конструктор с десятичным числом-инициализатором
        binaryNumber(int n) {
            objects++;
            if (n > positiveLimit || n < negativeLimit) {
                throw invalid_argument("десятичное число вне допустимого диапазона, введите другие аргументы");
            }
            int at = maxSize - 1;
            value = new int[maxSize];
            if (n >= 0) {
                value[0] = 0;

                while (n >= 1) {
                    value[at--] = n % 2;
                    n = n / 2;
                }

                for (int i = 1; i <= at; i++) {
                    value[i] = 0;
                }
            }
            else {
                value[0] = 1;
                n = 0 - n - 1;

                while (n >= 1) {
                    value[at--] = !(n % 2);
                    n = n / 2;
                }

                for (int i = 1; i <= at; i++) {
                    value[i] = 1;
                }
            }
        }


        binaryNumber& operator=(const binaryNumber& other) {
            for (int i = 0; i < maxSize; i++) {
                this->value[i] = other.value[i];
            }

            return (*this);
        }

        binaryNumber& operator+=(const binaryNumber& other) {
            adder(other);
            return (*this);
        }

        binaryNumber operator+(const binaryNumber& other) {
            return summator((*this), other);
        }

        //по значению, чтобы не изменять другое число
        binaryNumber operator-(binaryNumber other) {
            other.invertor();
            other.incrementor();
            return summator((*this), other);
        }

        binaryNumber operator*(const binaryNumber& other) {

            binaryNumber result;
            binaryNumber temp = (*this);
            for (int i = maxSize - 1; i >= 0; i--) {
                if (other.value[i] == 1) {
                    result += temp;
                    temp.printBinaryValue();
                    cout << endl;
                }

                temp.shiftLeft();
              //temp.printBinaryValue();
            }
            /*if (result[0] == 1) {
                result = result
            }*/

            return result;
        }

        int& operator[](size_t i) {
            return value[i];
        }

        int* getBinaryValue() {
            return value;
        }

        int getDecimalValue() {
            int result = 0;
            if (value[0] == 0) {
                for (int i = 1; i < maxSize; i++) {
                    if (value[i] == 1) {
                        result += pow(2, (maxSize - 1) - i); //8-1-0 = 7, 8-1 - 7 = 0
                    }
                }
            }
            else {
                for (int i = 1; i < maxSize; i++) {
                    if (value[i] == 0) {
                        result -= pow(2, (maxSize - 1) - i); //8-1-0 = 7, 8-1 - 7 = 0
                    }
                }

                result -= 1;
            }

            return result;
        }

        void printBinaryValue() {
            for (int i = 0; i < maxSize; i++) {
                cout << value[i];

            }
        }

        ~binaryNumber() {
            objects--;
            /*cout << "destruct" << endl;*/
            delete[] value;
        }
};






int main() {
    setlocale(LC_ALL, "RU");
    /*binaryNumber a(-5);
    binaryNumber b(25);
    b.printBinaryValue();
    cout << endl;*/
    while (true) {
        try {
            char op;
            int a, b;
            cout << "Битность - " << maxSize << "\nдля ввода доступны числа от " << negativeLimit << " до " << positiveLimit << endl;
            cout << "Выберите операцию (+, -, *): " << endl;
            cin >> op;
            cout << "Введите первый аргумент в десятичном виде: " << endl;
            cin >> a;
            binaryNumber aBinary(a);
            cout << "Введите второй аргумент в десятичном виде: " << endl;
            cin >> b;
            binaryNumber bBinary(b);
            binaryNumber cBinary;

            if (op == '+') {
                cBinary = aBinary + bBinary;
            }
            else if (op == '-') {
                cBinary = aBinary - bBinary;
            }
            else if (op == '*') {
                cBinary = aBinary * bBinary;
            }
            cout << "Первый аргумент в двоичном формате: ";
            aBinary.printBinaryValue();
            cout << endl;
            cout << "Второй аргумент в двоичном формате: ";
            bBinary.printBinaryValue();
            cout << endl;
            cout << "Результат в двоичном формате: ";
            cBinary.printBinaryValue();
            cout << endl;
            cout << "Результат в десятичном формате: " << cBinary.getDecimalValue() << endl;
            cout << "Objects: " << objects << endl;
            cout << endl;
        }
        catch (const std::exception& err)
        {
            cout << err.what() << endl;
            cout << endl;
        }
    }
    
    
    /*int* cValue = c.getBinaryValue();
    for (int i = 0; i < 32; i++) {
        cout << cValue[i];
    }*/

    return 0;
}
