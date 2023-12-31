#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<limits>
#include<algorithm>

typedef std::unordered_map<std::string, float> Mats;
typedef std::unordered_map<std::string, int> Ene;

class Node
{
private:
    std::string ename;
    int eap_cost;
    Mats eMaterials;
    Ene eEnemies;

public:
    Ene Enemies;
    void update(std::string n, int ap, Mats mats, Ene ene)
    {
        ename = n;
        eap_cost = ap;
        eMaterials = mats;
        eEnemies = ene;
        Enemies = eEnemies;
    }

    int ap_cost(){return eap_cost;}
    std::string name(){return ename;}
};

typedef std::unordered_map<Node*,int> NT;
typedef std::pair<NT, int> Pair;

bool checkMaps(Ene& res, Ene& ref) //See if all enemies are already present in the list.
{
    bool retval = true;
    for (auto x : ref)
    {
        if (res.find(x.first) != res.end())
        {
            auto i = res.find(x.first);
            if (i->second < x.second)
            {
                retval = false;
                return retval;
            }
        }

        else
        {
            retval = false;
            return retval;
        }
    }

    return retval;
}

void includeNode(Ene& res, Ene& ref, Ene& req) //Add enemy entries from node to the stack list of enemies.
{
    for (auto x : req)
    {
        if (ref.find(x.first) != ref.end())
        {
            res[x.first] += ref[x.first];
        }
    }
}

bool checkAvail(Ene& res, Ene& ref, Ene& req) //Check if ALL enemies are available.
{
    bool ret = true;
    Ene temp = req;
    for(auto x: temp)
    {
        if(res.find(x.first) != res.end())
        {
            temp[x.first] = temp[x.first] - res[x.first];
        }
    }

    for(auto x: temp)
    {
        if(ref.find(x.first) == ref.end() && x.second > 0)
        {
            ret = false;
            return ret;
        }
    }

    return ret;
}


//Check if a node has at least one from the remaining list of required enemies
bool checkNonzero(Ene& res, Ene& ref, Ene& req)
{
    bool ret = false;
    Ene temp = req;
    for(auto x: temp)
    {
        if(res.find(x.first) != res.end())
        {
            temp[x.first] = temp[x.first] - res[x.first];
        }
    }

    for(auto x: temp)
    {
        if(ref.find(x.first) != ref.end() && x.second > 0)
        {
            ret = true;
            return ret;
        }
    }

    return ret;
}

void effFarm(std::vector<Node*>& nodes, int n, Ene currEne, Pair visited, std::vector<Pair>& result, Ene& reqEne)
{
    if (n < 0)
    {
        return;
    }

    if(checkMaps(currEne, reqEne))
    {
        return;
    }

    if(!checkAvail(currEne, nodes[n]->Enemies, reqEne) && n == 0)
    {
        return;
    }

    //Excluded
    effFarm(nodes, n-1, currEne, visited, result, reqEne);


    //Run only if the node has at least one of the remaining required enemies.
    if(checkNonzero(currEne, nodes[n]->Enemies, reqEne))
    {   
        //Included

        visited.first[nodes[n]]++;
        visited.second += nodes[n]->ap_cost();

        includeNode(currEne, nodes[n]->Enemies, reqEne);

        if(checkMaps(currEne, reqEne))
        {
            result.push_back(visited);
            return;
        }

        // //Repeating the same node.
        effFarm(nodes, n, currEne, visited, result, reqEne);          
    }
}


//Function to take input.
void takeInput(Ene& reqEne, std::unordered_set<std::string>& availableEnm)
{
    int status = 1;
    while(true)
    {
        std::string ins = "BLANK";
        while(availableEnm.find(ins) == availableEnm.end())
        {
            std::cout << "Please enter the type of enemy. Enter DONE to confirm. \n";
            std::cin >> ins;
            if(ins == "DONE")
            {
                status = 0;
                break;
            }
            if( availableEnm.find(ins) == availableEnm.end() )
            {
                std::cout << "Enemy not found in database. \n";
            }
        }

        if(status == 0)
        {
            break;
        }

        int incount = 11;
        while(incount > 10 || incount < 1)
        {
            std::cout << "Please enter the count of enemies (1-10). Enter 99 to confirm. \n";
            std::cin >> incount;
            if(incount == 99)
            {   
                status = 0;
                break;
            }
            if( incount > 10 || incount < 1 )
            {
                std::cout << "Please enter in the range of 1 - 10 only. \n";
            }
        }

        if(status == 0)
        {
            break;
        }
        reqEne[ins] = incount;
    }
}

int main()
{
    // Data starts here. v 

    Ene eneA;
    eneA["A"] = 3;

    Ene eneB;
    eneB["A"] = 1;
    eneB["B"] = 2;

    Ene eneC;
    eneC["A"] = 1;
    eneC["B"] = 1;
    eneC["C"] = 1;

    Ene eneD;
    eneD["D"] = 1;
    eneD["E"] = 1;

    Ene eneE;
    eneE["G"] = 3;
    eneE["F"] = 2;

    Ene eneF;
    eneF["D"] = 5;

    Mats matEmpty;

    Node* x = {new Node};
    x->update("Node1", 20, matEmpty, eneA);

    Node* y = {new Node};
    y->update("Node2", 21, matEmpty, eneB);

    Node* z = {new Node};
    z->update("Node3", 22, matEmpty, eneC);

    Node* n4 = {new Node};
    n4->update("Node4", 25, matEmpty, eneD);

    Node* n5 = {new Node};
    n5->update("Node5", 18, matEmpty, eneE);

    Node* n6 = {new Node};
    n6->update("Node6", 30, matEmpty, eneF);

    std::vector<Node*> allNodes = {x,y,z,n4,n5,n6};
    std::unordered_set<std::string> availableEnm;
    for(Node* n: allNodes)
    {
        for(auto x: n->Enemies)
        {
            availableEnm.insert(x.first);
        }
    }

    std::unordered_map<std::string, std::vector<Node*>> umap;

    for(Node* i: allNodes)
    {
        for(auto x: i->Enemies)
        {
            umap[x.first].push_back(i);
        }
    }

    // ^ Data ends here. 

    std::unordered_set<Node*> eligibleNodes; //To find nodes which contain one or more of the given Enemies.

    Ene reqEne; //Required enemies. (Can be changed to input to console or through GUI if needed)
    takeInput(reqEne, availableEnm);

    for(auto x: reqEne)
    {
        if(umap.find(x.first) != umap.end())
        {
            for(Node* n: umap[x.first])
            {
                eligibleNodes.insert(n);
            }
        }
    }

    std::vector<Node*> nodes;

    for(auto i: eligibleNodes)
    {
        nodes.push_back(i);
    }

    //Initializing variables for the function
    Ene currEne; 
    Pair visited;
    visited.second = 0;
    std::vector<Pair> result;

    //Calling function
    effFarm(nodes, nodes.size() - 1, currEne, visited, result, reqEne);

    //Sorting according to the stamina cost with lambda function (Lowest to Highest)
    std::sort(result.begin(), result.end(), [](Pair a, Pair b){
        return a.second < b.second;
    }); 


    //Printing the recommended nodes in order
    for(Pair p: result)
    {
        std::cout << "\nRun/Play ";

        for(auto x: p.first)
        {
            std::cout << x.first->name() << ": " << x.second << " time(s), ";
        }

        std::cout << "at the cost of " << p.second << " AP. \n";
    }

    return 0;
}
