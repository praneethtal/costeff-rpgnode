# costeff-rpgnode
(Beginner CPP Project) Calculates combinations of stages/nodes in an RPG to meet the required amounts of types of enemies to be defeated.

Principle:
"Node" in this context means a stage in the game. Each stage has different types of rewards, enemies, and even costs different amount of stamina. Stamina here is represented by AP. Node class consists of: Node's name, Node's AP cost, Node's material rewards, Node's enemies. Some video game quests require you to defeat a given amount of certain enemies.
This program should be able to find the nodes which contain the required enemies, and then find different combinations of all the whitelisted nodes, sort the combinations, and print out the combinations in ascending order of their cost.

'effFarm' function does the computation by taking in a vector of the whitelisted nodes, some other data structures storing the result, required enemies, some temporary structures to hold and pass data during recursive calls. Functions goes as follows:

1. Check if n < 0. (Since we are starting from back element of the vector)

2. checkMaps checks if we met the required amount of enemies.

3. checkAvail checks if the last node has all the remaining amount of enemies. Return if not, since there's no other element beyond the last one.

4. Calls function for n-1.

5. After n-1 function returns, check if the current node's elements are required or not.

6. If yes, add the enemy count from the node to a stack containing enemy entries so far.

7. Check if the requirement is met. If yes, return.

8. If not, repeat the function.

9. The results are stored in a vector of a pair of <unordered_map,int> where unordered_map contains the nodes/stages and how many times we're supposed to play or beat them. And the int is the total AP cost for all the nodes in the map.

10. Then we sort the resulting vector using std::sort and lambda function, such that they're sorted in ascending order of the pair's second value (AP cost).

11. The nodes are printed.
