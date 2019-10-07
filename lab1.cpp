#include "common.h"

using namespace Minisat;

bool havethestone(int index,int button[])
{
    if(button[0]==index)
      return true;
    if(button[1]&&button[1]==index)
      return true;  
    return false;  
}


bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{
    Solver solver;
    Var variables[1000];
    int i, j;
    for(i = 0; i<m; ++i) //m=the number of buttons
        variables[i] = solver.newVar();

    for(j = 0; j<n; ++j)
       {
           if(states[j]==0)
           {
            int x=-1,y=-1;
            for(i = 0; i<m; i++)
             if(havethestone(j+1,button[i]))
             {
              if(x==-1) {x=i;continue;}
              if(y==-1) {y=i;break;}
             }
             if(x!=-1&&y!=-1)
             {
                 solver.addClause(mkLit(variables[x]),mkLit(variables[y]));
                 solver.addClause(~mkLit(variables[x]),~mkLit(variables[y]));
             }
             if(x!=-1&&y==-1)
             {
                 solver.addClause(mkLit(variables[x]));
             }
             if(x==-1&&y!=-1)
             {
                 solver.addClause(mkLit(variables[y]));
             }
             if(x==-1&&y==-1)
             {
                 return false;
             }
           }
           if(states[j]==1)
           {
            int x=-1,y=-1;
            for(i = 0; i<m; i++)
             if(havethestone(j+1,button[i]))
             {
              if(x==-1) {x=i;continue;}
              if(y==-1) {y=i;break;}
             }
             if(x!=-1&&y!=-1)
             {
                 solver.addClause(mkLit(variables[x]),~mkLit(variables[y]));
                 solver.addClause(~mkLit(variables[x]),mkLit(variables[y]));
             }
             if(x!=-1&&y==-1)
             {
                 solver.addClause(~mkLit(variables[x]));
             }
             if(x==-1&&y!=-1)
             {
                 solver.addClause(~mkLit(variables[y]));
             }
           }
       }
    //TODO : your solution here.


    //solve SAT problem
    auto sat = solver.solve();
    if(sat)
    {
        for(i = 0; i < m; ++i)
            answer[i] = (solver.modelValue(variables[i]) == l_True);
        return true;
    }
    return false;
}



