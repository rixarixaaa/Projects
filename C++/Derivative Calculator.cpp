//Parisa Nawar pxn210032
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

enum TrigType { COSINE, SINE };

template<class T> class ProjNode {
    public:
        T data;
        ProjNode* next;
        
        ProjNode() {
            next = NULL;
        }
        
        ProjNode(T data) {
            next = NULL;
            this->data = data;
        }
}; 

template<class T> class ProjLinkedList {
    public:
        ProjNode<T>* head;
        
        ProjLinkedList() {
            head = NULL;
        }
        
        void add(T data) {
            ProjNode<T>* newNode = new ProjNode<T>(data);
            
            if(!head) {
                head = newNode;
                head->next = NULL;
            }
            else {
                newNode->next = head;
                head = newNode;
            }
        } 
        
        T getAt(int n) {
            ProjNode<T>* retNode = head;
            int x = 0;
            
            while(x != n) {
                retNode = retNode->next;
                x++;
            }
            
            return retNode->data;
        } 
        
}; 

class AbstractTerm {
    public:
        virtual AbstractTerm* derivative() = 0;
        virtual double evaluate(double) = 0;
        virtual string toString() = 0;
        virtual int rank() = 0;
        virtual int getA() = 0;
};

class Expression {
    private:
        ProjLinkedList<AbstractTerm*>* absTerm;
        
    public:
        Expression() {
            absTerm = new ProjLinkedList<AbstractTerm*>();
        }
        
        Expression* getDerivative() {
            ProjNode<AbstractTerm*>* t = absTerm->head;
            Expression* e = new Expression();
            
            while(t != NULL) {
                e->absTerm->add(t->data->derivative());
                t = t->next;
            }
            return e;
        } 
        
        double getEvaluation(double v) {
            ProjNode<AbstractTerm*>* t = absTerm->head;
            double total = 0;
            
            while(t != NULL) {
                total += t->data->evaluate(v);
                t = t->next;
            }
            return total;
        } 
        
        string toString() {
            string retEx = "";
            ProjNode<AbstractTerm*>* p = absTerm->head;
            ProjNode<AbstractTerm*>* c = absTerm->head->next;
            
            while(c != NULL) {
                if(c->data->rank() < p->data->rank()) {
                    p->next = c->next;
                    c->next = absTerm->head;
                    absTerm->head = c;
                    c = p;
                }
                else {
                    p = c;
                }
                
                c = c->next;
            }
            
            p = absTerm->head;
            c = absTerm->head->next;
            
            while(c != NULL) {
                if(c->data->rank() < p->data->rank()) {
                    p->next = c->next;
                    c->next = absTerm->head;
                    absTerm->head = c;
                    c = p;
                }
                else {
                    p = c;
                }
                
                c = c->next;
            }
            
            ProjNode<AbstractTerm*>* t = absTerm->head;
            
            while(t != NULL) {
                if(t->data->toString() == "+ 0 ") {
                    t = t->next;
                }
                else {
                    retEx += t->data->toString();
                    t = t->next;
                }
            }
            
            
            return retEx;
        }
        
        void operator+=(AbstractTerm* ab) {
            absTerm->add(ab);
        }
}; 

class ConstantTerm: public AbstractTerm {
    private:
        int a;
        
    public:
        ConstantTerm(int a) {
            this->a = a;
        }
        
        int rank() {
            return 3;
        }
        
        int getA() {
            return a;
        }
        
        AbstractTerm* derivative() {
            a = 0;
            AbstractTerm* newDer = new ConstantTerm(a);
            return newDer;
        }
        
        double evaluate(double val) {
            return (a) + (val * 0);
        }
        
        string toString() {
            string s;
            
            if(a > 0) {
                s = "+ " + to_string(a) + " ";
            }
            else if (a < 0) {
                s = "- " + to_string(abs(a)) + " ";
            }
            else if(a == 0) {
                s = "+ 0 ";
            }
            
            return s;
        }
};

class LinearTerm: public ConstantTerm {
    private:
        int a;
        
    public:
        LinearTerm(int a) : ConstantTerm(a) {
            this->a = a;
        }
        
        int rank() {
            return 2;
        }
        
        int getA() {
            return a;
        }
        
        AbstractTerm* derivative() {
            AbstractTerm* newDer = new ConstantTerm(a);
            return newDer;
        }
        
        double evaluate(double val) {
            return a * val;
        }
        
        string toString() {
            string s;
            
            if(a > 0) {
                     s = "+ " + to_string(a) + "x" + " ";
            }
            else if (a < 0) {
                    s = "- " + to_string(abs(a)) + "x" + " ";
            }
            
            return s;
        }
};

class PolynomialTerm: public LinearTerm {
    private:
        int a;
        int b;
        int coefficient;
        int exponent;
        
    public:
        PolynomialTerm(int a, int b) : LinearTerm(a) {
            this->a = a;
            this->b = b;
        } 
        
        int rank() {
            return 1;
        }
        
        int getA() {
            return a;
        }
        
        AbstractTerm* derivative() {
            AbstractTerm* newDer;
            
            if(b > 2) {
                coefficient = a * b;
                exponent = b - 1;
                newDer = new PolynomialTerm(coefficient, exponent);
            }
            else if (b == 2) {
                coefficient = a * 2;
                exponent = 1;
                newDer = new LinearTerm(coefficient);
            }
            
            return newDer;
        }
        
        double evaluate(double val) {
            return pow(val, b) * a;
        }
        
        string toString() {
            string s;
            
            if(a > 0) {
                    s = "+ " + to_string(a) + "x^" + to_string(b) + " ";
            }
            else if (a < 0) {
                    s = "- " + to_string(abs(a)) + "x^" + to_string(b) + " ";
            }
            
            return s;
        }
};

class TrigTerm: public LinearTerm {
    private:
        int a;
        TrigType t;
        
    public:
        TrigTerm(int a, TrigType t) : LinearTerm(a) {
            this->a = a;
            this->t = t;
        }
        
        int getA() {
            return a;
        }
        
        int rank() {
            int r;
            
            if(t == SINE) {
                r = 4;
            }
            else if(t == COSINE) {
                r = 5;
            }
            
            return r;
        }
        
        AbstractTerm* derivative() {
            if(a > 0) {
                if(t == COSINE) {
                    a *= -1;
                    t = SINE;
                }
                else if(t == SINE) {
                    t = COSINE;
                }
            }
            else if (a < 0) {
                if(t == COSINE) {
                    a *= -1;
                    t = SINE;
                }
                else if(t == SINE) {
                    t = COSINE;
                }
            }
            
            AbstractTerm* newDer = new TrigTerm(a, t);
            return newDer;
        }
        
        double evaluate(double val) {
            double eval;
            
            if(t == COSINE) {
                eval = a * cos((val * M_PI) / 180);
            }
            else if(t == SINE) {
                eval = a * sin((val * M_PI) / 180);
            }
            
            return eval;
        }
        
        string toString() {
            string s;
            
            if(a > 0) {
                if(t == COSINE){
                    s = "+ " + to_string(a) + "cos(x)" + " ";
                }
                else if(t == SINE) {
                    s = "+ " + to_string(a) + "sin(x)" + " ";
                }
            }
            else if (a < 0) {
                if(t == COSINE) {
                    s = "- " + to_string(abs(a)) + "cos(x)" + " ";
                }
                else if(t == SINE) {
                    s = "- " + to_string(abs(a)) + "sin(x)" + " ";
                }
            }
            
            return s;
        }
}; 


int main()
{
    return 0;
}













