#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void dfs(vector<vector<float>> &result_matrix,vector<int> & visited,vector<int> &result_greedy,int ele)
{  // cout<<ele<<" ";
    if(visited[ele]==1)
        return ;
    else
    {
        visited[ele]=1;
        result_greedy.push_back(ele);
        for(int i=0;i<result_matrix.size();i++){
            if(visited[i]==0 && result_matrix[ele][i]!=0)
            {

               dfs(result_matrix,visited,result_greedy,i);
            }
        }
    }
}
vector<int> cycle(vector<vector<float>> &result_matrix)
{
    vector<int>visited(result_matrix.size(),0);
    vector<int> result_greedy;
    dfs(result_matrix,visited,result_greedy,0);
    /*cout<<endl<<" path printed "<<endl;
    for(int i=0;i<result_greedy.size();i++)
    {
        cout<<result_greedy[i]<<" ";
    }
    cout<<endl;*/
    return result_greedy;
}
int parent(int var,vector<int> &root)
{
while(root[var]!=var)
  {
    root[var]=root[root[var]];
    var=root[var];
  }
    return var;
}
bool cmp(pair<float,pair<int,int>> a,pair<float,pair<int,int>> b)
{
  return a.first < b.first;
}
pair<float,vector<int>> greedy_TSP(vector<vector<float>> & matrix)
{

vector<int> root(matrix.size(),INT_MAX);
vector<vector<float>> result_matrix;
for(int i = 0;i <matrix.size();++i)
    {
        root[i] = i;
    }
vector<float> set_zero(matrix.size(),0.0);
for(int i=0;i<matrix.size();i++)
{
  result_matrix.push_back(set_zero);
}


  vector <pair <float , pair <int ,int >>> edge_array;

  vector<int> visited(matrix.size(),0);

  for(int i=0;i<matrix.size();i++)
  {
    for(int j=0;j<matrix[i].size();j++)
    {
      if(matrix[i][j])
    {  edge_array.push_back({matrix[i][j],{i,j}}); }

    //  cout<<edge_array[i].first<<" "<<edge_array[i].second.first<<" "<<edge_array[i].second.first<<endl;

    }
  }

  sort(edge_array.begin(),edge_array.end(),cmp);
  /*
  for(int i=0;i<edge_array.size();i++)
  {
    cout<<edge_array[i].first<<" "<<edge_array[i].second.first<<" "<<edge_array[i].second.second<<endl;
  }*/

  int a,b;
  float cost,minCost=0;
  for(int i=0;i<edge_array.size();i++)
  {
    a=edge_array[i].second.first;
    b=edge_array[i].second.second;
    cost=edge_array[i].first;
  //  cout<<a<<" "<<b<<" "<<cost<<endl;
    if(parent(a,root)!=parent(b,root) && (visited[a]<2 && visited[b]<2))

    {
      minCost+=edge_array[i].first;
      visited[a]++;
      visited[b]++;
      result_matrix[a][b]=cost;
      result_matrix[b][a]=cost;
      int x=parent(a,root);
      int y =parent(b,root);
      root[x]=root[y];
    }

  }/*
  for(int i=0;i<matrix.size();i++)
  {
    cout<<" "<<visited[i];
  }
  cout<<endl;
  */
  float doubt=0;
  /*
  for(int i=0;i<result_matrix.size();i++)
  {
    for(int j=0;j<result_matrix[i].size();j++){
      cout<<result_matrix[i][j]<<" ";
      doubt+=result_matrix[i][j];
    }cout<<endl;
  }
*/
  int cycle_a,cycle_b;
  for(int i=0;i<visited.size();i++){
    if(visited[i]==1)
        {
        cycle_a=i;
        visited[i]=2;
        break;
        }
  }
  for(int i=0;i<visited.size();i++){
    if(visited[i]==1)
        {
        cycle_b=i;
        visited[i]=2;
        break;
        }
  }

  //cout<<endl<<" : "<<matrix[cycle_a][cycle_b]<<endl;
  minCost+=matrix[cycle_a][cycle_b];
  doubt+=(matrix[cycle_a][cycle_b]*2);
  //cout<<"answer is : "<<doubt/2<<endl;

  vector<int> ans_greedy=cycle(result_matrix);
  pair<float,vector<int>> abc=make_pair(minCost,ans_greedy);
    return abc;
}
float summation(vector<int> array,vector<vector<float>> &matrix,float sum)
{
  for(int j=0;j<array.size()-1;j++)
  {
    sum+=matrix[array[j]][array[j+1]];
  }
  sum+=matrix[array[array.size()-1]][array[0]];
  return sum;
}
int main()
{
  string x;
  getline(cin, x);
  int n;
  cin>>n;
  float xcor,ycor;
  for(int i=0;i<n;i++)
  {
    cin>>xcor>>ycor;
  }
  vector<float> temp(n,0.0);
  float MIN=100000;
  vector<int> final_result(n,0);
  vector<vector<float>> matrix;
  for(int i=0;i<n;i++)
  {
    matrix.push_back(temp);
  }
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      cin>>matrix[i][j];
    }
  }
  for(int row=0;row<n;row++)
  {

    for(int col=0;col<n;col++)
    {
      if(row==col)
      continue;

      vector<int> arr;
      float min_value=100000.00;int index,index1;
      //cout<<row<<" "<<col<<endl;
      arr.push_back(row);
      arr.push_back(col);
      float sum=0.0;
      vector<int> visited(n,0);
     visited[row]=1;
      visited[col]=1;
      sum+=matrix[row][col];
      index=col;int count=2;
      while(count<=n){
        min_value=100000.00;
        for(int it=0;it<n;it++)
        {
          if(!visited[it] && min_value>matrix[index][it] && index!=it &&matrix[index][it]>0)
          {
            index1=it;
            min_value=matrix[index][it];

          }
        }
        //cout<<"index :"<<index<<" index_1 : "<<index1<<endl;
        if(index!=index1){
          arr.push_back(index1);
          //cout<<index1<<" ";
          visited[index1]=1;
          sum+=matrix[index][index1];
          index=index1;
        }
        else{
          sum+=matrix[index1][row];
        //  cout<<"\n sum : "<<sum<<endl;
          if(MIN>sum){
          MIN=min(sum,MIN);
          final_result=arr;
        }
        }
        count++;
      }/* cout<<"path :";
      for(int i=0;i<arr.size();i++)
      {
        cout<<arr[i]<<" ";
      }
      cout<<endl;*/
    }//cout<<row<<" "<<MIN<<" "<<endl;
  }
  //cout<<"minimum cost path : "<<MIN<<endl;

  pair<float,vector<int >> cba = greedy_TSP(matrix);
//  cout<<" greedy : "<<cba.first<<" , nearest-neighbour : "<<MIN<<endl;
  if(cba.first>=MIN){
  for(int i=0;i<n;i++)
  {
    cout<<final_result[i]<<" ";
  }
}
else{
  for(int i=0;i<n;i++)
  {
    cout<<cba.second[i]<<" ";
  }
}

  //cout<<endl<<"check correct or not : "<<summation(final_result,matrix,0);
  return 0;
}
//35 25 27 4 42 45 24 44 23 12 5 28 1 26 36 48 6 2 22 10 19 40 11 14 46 0 7 43 18 33 38 49 13 21 31 37 9 20 3 15 30 39 47 29 41 16 8 32 34 17
/*
70 11 123 46 127 55 72 191 139 0 169 15 31 3 57 7 170 40 90 1 28 9 74 253 53 142 155 102 95 4 14 230 178 120 234 226 134 218 26 91 107 18 13 64 222 32 87 61 56 33 100 143 76 59 124 93 137 220 133 135 128 174 249 187 103 145 167 199 19 221 164 185 99 80 149 27 177 192 209 173 215 10 38 41 86 36 180 202 37 157 196 67 158 69 176 248 119 131 25 168 121 161 163 34 254 251 42 204 162 60 212 97 110 39 85 188 151 108 130 20 166 206 73 77 189 246 208 213 205 159 184 171 48 122 68 78 197 144 194 58 79 6 146 160 232 21 94 217 165 201 88 193 132 227 112 245 219 195 156 51 236 12 92 62 81 75 186 84 179 175 114 239 252 241 129 5 183 152 138 82 141 115 24 150 242 2 29 250 125 35 43 17 198 214 154 65 181 104 113 136 16 47 30 71 89 140 228 231 182 223 23 243 50 190 54 200 211 233 96 117 109 172 240 66 237 255 207 225 235 153 210 52 116 126 45 148 22 105 106 83 44 8 98 111 203 224 63 101 244 216 147 49 238 247 118 229


68 56 16 84 5 61 43 49 66 50 41 97 53 74 27 10 62 73 75 94 59 44 89 17 31 51 70 9 11 77 24 79 34 1 32 45 38 67 13 83 2 58 26 93 30 28 63 55 60 14 48 39 29 82 78 88 81 76 23 15 72 35 95 3 99 85 8 69 87 36 92 86 22 96 12 80 33 71 98 6 4 0 91 47 64 52 40 7 25 46 54 19 20 18 21 65 90 57 37 42

*/
