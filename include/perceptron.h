#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <vector>
using namespace std;
class perceptron
{
    int input_num,output_num;
    float **w;
    float *b;

public:

    perceptron(int input_num,int output_num);
    ~perceptron();

    int train(vector< vector<float> > &x, vector<int> &y, const int max_epoch,float lr,bool delta_rule);
    float test(vector< vector<float> > &x, vector<int> &y);
    void print_weights();
};

#endif // PERCEPTRON_H
