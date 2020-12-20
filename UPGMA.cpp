#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

//string orgamisms_names[]={"Cavia_porcellus","Rattus_norvegicus","Mus_musculus","Mesocricetus_auratus","Felis_catus","Canis_lupus_familiaris","Equus_caballus","Homo_sapiens","Gorilla","Macaca_mulatta"};
string orgamisms_names[]={"","PIG","RAT","MOUSE","HAMSTER","CAT","DOG","GORILA","HUMAN","HORSE","MONKEY"};

class UPGMA
{
    public:
    int row, col;
    float ** matrix;
    float value;
    vector<string> organisms;
    string file;
    UPGMA() //default constructor
    {
        row=11;
        col=11;
        organisms={"a","b","c","d","e","f","g","h","i","j","k"};
    }

  UPGMA (string file_name, int row, int col) 
    : file(file_name), row(row), col(col) 
    {
        this->matrix = creatematrix(row, col);
        this->Loadmatrix();
    }
// this function creates a zero matrix with the dimensions given when declaring a UPGMA class.
    float** creatematrix(int x, int y) //return a pointer to a pointer to this matrix
    {
        float ** m;
        m = new float*[x];
        for (int i=0; i<x; ++i) 
        { 
            m[i] = new float[y];
            for (int j=0; j<y; ++j)
            {
                m[i][j] =0;
            }
        }
        return m;
    }

//this function read the file containing the identity matrix and put it in the zero matrix created by creatmatrix() and making sure that m[i,x]= m[x,i]
    void Loadmatrix() 
    {
        ifstream in(this->file);
        if (!in) 
        {
            cout << "Cannot open file.\n";
            return;
        }
        string line;
        for( int x = 0; getline( in, line ); ) 
        {
            int i = 0;
            stringstream ma(line);
            while (ma.good() && i < this->row)
            {
              ma >> this->matrix[x][i];
              this->matrix[i][x] =  this->matrix[x][i];
              ++i;
            }
            organisms.push_back(orgamisms_names[x]);
            ++x;            
        }
        in.close();
    }


//this function print the matrix resulted after each cluster
    void printmatrix(float ** matrix, vector<string> organisms, int row, int col)
    { 
        cout << "\n-";
        for (int x = 0; x < organisms.size(); ++x)
        {
            cout << setw(10) << organisms.at(x);   
        }
        cout<<"\n";
        for (int x = 0; x < row; ++x) 
        {
            cout << organisms.at(x);
            for (int y = 0; y < col; ++y) 
            {
                cout <<  setw(10)<<*(*(matrix + x) + y);
            }
            cout << endl;
        }
    }

    //this function find the value with the highest precentage identity (i.e the value where 2 species are closest to each other)
    //and print this value , its position and the 2 taxa it was found between
    vector<int> minimum_value(vector<string> organisms, float** matrix,int row, int col) 
    {
        int positions[2] = {1, 0};
        this->value = 0;
        bool flag = false;
        for (int x = 1; x < row; ++x) 
        {
            for (int y = 0; y < x; ++y) 
            {
                if ( flag && matrix[x][y] > this->value ) 
                {
                  positions[0] = x;
                  positions[1] = y;
                  this->value = matrix[x][y];
                }
                else
                {
                  flag = true;
                }
            }
        }
        vector<int> pos;
        for (int u=0; u<2; ++u)
        {
            pos.push_back(positions[u]);
        }
        cout << "\nMin: " << this->value << ", position("<<pos.at(0) << ", " <<pos.at(1)<< "), new: " << organisms[pos.at(0)] <<","<< organisms[pos.at(1)];
        return pos;
    }
//this function uses the positions extracted from minimum_value function to build the cluster by taking the average between them and other pints in the matrix
//then call the printing function to print the new matrix. it keeps redoing that until the all elements are clustered nd the last matrix is size 2x2
// every cluster and the distance between them are saved in a file called tree.txt
    void Build_Cluster() 
    {
        ofstream out("tree.txt");
        cout << "\n Original matrix: \n";
        printmatrix(this->matrix, this->organisms, row, col);
        int clusters = row;
        float ** currentmatrix = this->matrix;
        float ** new_matrix;
        string result;
          vector<string> new_organisms = this->organisms;
          while(clusters > 2) 
          {
            cout << "\n*******************************************************************\n";
            vector<int> min_position = minimum_value(new_organisms, currentmatrix, clusters, clusters);
            vector<string> tmp_organisms;
            for (int u=0; u<new_organisms.size(); ++u) 
            {
                if (u != min_position.at(0) && u != min_position.at(1))
                {
                    tmp_organisms.push_back(new_organisms.at(u));
                }
            }
              tmp_organisms.push_back("("+new_organisms.at(min_position.at(0))+","+ new_organisms.at(min_position.at(1)) +")");
              result = "("+new_organisms.at(min_position.at(0))+","+ new_organisms.at(min_position.at(1))+"):"+std::to_string(this->value);
              out << result << endl;
              clusters --;        
              new_matrix = creatematrix(clusters, clusters);
              int temp_x = 0;
              // set new matrix
              cout <<  endl << " Clusters: " << clusters;
              for (int x=0; x<clusters+1; ++x) 
              {
                  int temp_y = 0;
                  if (x!=min_position.at(0) && x!=min_position.at(1)) 
                  {
                    for (int y=0; y<clusters+1; ++y) 
                    {
                        if (y!=min_position.at(0) && y!=min_position.at(1)) 
                        {
                            new_matrix[temp_x][temp_y] = currentmatrix[x][y];
                            temp_y++;
                        }
                    }
                    temp_x++;
                  }
              }
              if (clusters == 2) 
              {
                  float sum = 0;
                  for (int u=1; u<3; ++u) 
                  {
                      sum += currentmatrix[0][u];
                  }
                  new_matrix[1][0] = sum/2;
                  new_matrix[0][1] = new_matrix[1][0];
                  string temp = "(("+tmp_organisms.at(0)+ ")" + tmp_organisms.at(1)+"):"+std::to_string(new_matrix[1][0])+ ");";
                  out <<  temp;                 
              }
              else 
              {
                  int u = 0;
                  for (int x=0; x<clusters+1; ++x) 
                  {
                      if (x!=min_position.at(0) && x!=min_position.at(1) ) 
                      {
                        float sum = (currentmatrix[min_position.at(0)][x] + currentmatrix[min_position.at(1)][x]);
                        new_matrix[temp_x][u] = sum/2;
                        new_matrix[u][temp_x] = new_matrix[temp_x][u];
                        u++;
                      }
                  }
              }
              cout << "\n New matrix: \n";
              printmatrix(new_matrix, tmp_organisms, clusters, clusters);
              currentmatrix = new_matrix;
              new_organisms = tmp_organisms;
          }
          out.close();
      }

      
      ~UPGMA() //class destructor 
      {
        for (int i = 0; i < this->row; ++i) 
        {
            delete[] this->matrix[i];
        }
        delete[] this->matrix;
      }
};

int main() 
{
    UPGMA *Cluster = new UPGMA("mydata.txt", 11, 11);
    Cluster->Build_Cluster();
    return 0;
}