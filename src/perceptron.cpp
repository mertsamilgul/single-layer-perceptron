#include <iostream>
#include "perceptron.h"

perceptron::perceptron(int input_num,int output_num)
{
    this->input_num = input_num;
    this->output_num = output_num;

    w = new float*[input_num];
    for(int i=0;i<input_num;i++)
        w[i] = new float[output_num]{0};

    for(int i=0;i<input_num;i++)
        for(int j=0;j<output_num;j++)
            w[i][j]=0;


    b = new float[output_num]{0};

    for(int j=0;j<output_num;j++)
        b[j]=0;

}

perceptron::~perceptron()
{
    for(int i=0;i<input_num;i++)
        delete[] w[i];

    delete[] b;
}

int perceptron::train(vector< vector<float> > &input, vector<int> &output, const int max_epoch)
{
    float y_in; // agirlikli toplam sonucu
    float y; // aktivasyon fonksiyonu sonucu
    float th=0.5; // threshold degeri
    float lr = 0.001;

    int i=0;
    bool same=false;

    while(i < max_epoch && !same) // belirlenen max epoch'a ulasana kadar
    {                             // veya tamamen egitilene kadar devam

        same=true;

        //cout << i << ". epoch " << endl;

        for(int j=0;j<input.size();j++)
        {

            int target_1 = output[j]; // hangi sonucun 1 cikmasi
                                      // gerektigi tutulur.
            int t;


            for(int z=0;z<output_num;z++)
            {
                y_in=b[z];

                for(int k=0;k<63;k++)
                    y_in += input[j][k]*w[k][z];


                if(y_in > th)         //
                    y=1;              //
                else if(y_in < -1*th) //  aktivasyon fonksiyonu.
                    y=-1;             //
                else                  //
                    y=0;              //
                if(z == target_1)
                    t=1;
                else
                    t=-1;

                //cout << z << ": " << y << " | ";

                if(y!=t)
                {
                    //cout << " E ";

                    for(int k=0;k<63;k++) // agirliklar guncellenir
                        w[k][z] = w[k][z] + lr*t*input[j][k];

                    b[z] = b[z] + lr*t; // bias guncellenir

                    same = false;
                }
            }

            //cout << endl;
        }

        //cout << endl;
        i++;
    }
    return i;
}

float perceptron::test(vector< vector<float> > &input, vector<int> &output)
{
    float th=0.2;
    float y;
    int error=0;

    for(int j=0;j< input.size();j++)
    {

        int target_1 = output[j]; // hangi sonucun 1 digerlerinin
                                  // -1 oldugu tutulur.
        int t;

        bool error_occured = false;

        for(int z=0;z<output_num;z++)
        {
            float y_in=b[z];

            for(int k=0;k<input[j].size();k++)
                y_in += input[j][k]*w[k][z];

            if(y_in > th)         //
                y=1;              //
            else if(y_in < -1*th) //  aktivasyon fonksiyonu.
                y=-1;             //
            else                  //
                y=0;              //
            if(z == target_1)
                t=1;
            else
                t=-1;

            if(y!=t)
                error_occured = true;
        }

        if(error_occured)
            error++;
    }

    return (input.size()-(float)error)/input.size();
}



