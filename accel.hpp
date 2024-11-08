#include<iostream>
#include<vector>
using namespace std;

template <class T>
class Accel{

    private:

        T instance;
        typedef decltype(instance.val) R;
        int operatorSize=instance.functionList.size();

        class ValueWrapper {
    public:
        vector<R> valueList;
        int degree = 0;

        ValueWrapper(int listSize, T& instance) {
            degree = 0;
            try {
                valueList = instance.identities;
            } catch (exception& e) {
                cerr << e.what() << '\n';
                valueList.resize(listSize, instance.val);
            }
        }

        ValueWrapper(vector<R>& valueList1, int degree1 = 1) : valueList(valueList1), degree(degree1) {}
        ValueWrapper(vector<R>&& valueList1, int degree1 = 1) : valueList(std::move(valueList1)), degree(degree1) {}
    };


        ValueWrapper applyOperators(ValueWrapper& x, ValueWrapper& y){

            ValueWrapper result=x;  
            result.degree+=y.degree;
            R cummulant= x.valueList[0];
            result.valueList[0]=(instance.functionList[0])(x.valueList[0],y.valueList[0]);

            for(int i=1;i<result.valueList.size();i++){
                R postFactor= (instance.functionList[i-1])(cummulant,y.valueList[i]);
                cummulant=(instance.functionList[i])(cummulant,x.valueList[i]);
                result.valueList[i]=(instance.functionList[i])(result.valueList[i],postFactor);
            }
            
            return result;

        }

        ValueWrapper applyOperators(ValueWrapper&& x, ValueWrapper&& y){
            ValueWrapper a=x,b=y;
            return applyOperators(a,b);
        }

        void calcerateUtil(int n, ValueWrapper& temp, ValueWrapper& start){

            while(n){
                if(n&1){
                    start=applyOperators(start,temp);
                }
                temp=applyOperators(temp,temp);
                n>>=1;
            }

        }

    public:

        Accel(){}

        Accel(T& instance1) : instance(instance1), operatorSize(instance.functionList.size()) {}

        R calcerate(R& operand, long long n){
            
            if(n<=0){
                return instance.id;
            }

            n--;
            ValueWrapper temp(vector<R> (operatorSize,operand),1);
            ValueWrapper start(vector<R> (operatorSize,operand),1);

            calcerateUtil(n,temp,start);

            return start.valueList.back();

        }

        R calcerate(R&& operand, long long n){
            R operand1=operand;
            return calcerate(operand1,n);
        }

        R calcerate(R& operand, long long n, R& startingPoint){

            if(n<=0){
                return instance.id;
            }

            ValueWrapper temp(vector<R> (operatorSize,operand),1);
            ValueWrapper start(instance.identities,0);
            start.valueList[0]=startingPoint;

            calcerateUtil(n,temp,start);

            return start.valueList.back();
            
        }

        R calcerate(R&& operand, long long n, R&& startingPoint){

            R operand1=operand;
            R startingPoint1=startingPoint;

            return calcerate(operand1,n,startingPoint1);
            
        }

};

template <typename R>
class OperatorClass{

    public:
        R id;
        R val;
        vector<R> identities;
        vector<R (*)(R,R)> functionList;
        
        OperatorClass(vector<R (*) (R,R)> &functionList1,vector<R> &identities1){

            functionList=functionList1;
            identities=identities1;

        }

        OperatorClass(){}

};