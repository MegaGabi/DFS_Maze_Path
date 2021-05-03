#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

struct Point
{
  int x, y;
};

struct Graph
{
  vector<Graph*> adj;
  Point point;
};

Point getMazeSize(string graph)
{
    size_t width = graph.find_first_of('\n');
    return Point{static_cast<int>(width - 1), static_cast<int>((graph.size() / width) - 1)};
}

Graph* stringToGraph(string graph)
{
    queue<Graph*> path;
    Graph* origin = new Graph();
    origin->point = Point{0, 0};
    path.push(origin);
  
    graph.erase(graph.begin());
  
    int x = 0, y = 0;
    for(const auto& c : graph)
    {
      if(c == 'W')
      {
        ++x;
      }
      else if(c == '.')
      {
        ++x;
        Graph* node = new Graph();
        node->point = Point{x, y};
        if(!path.empty())
        {
          auto previous_x = path.back();
          auto previous_y = path.front();
          
          if(previous_y->point.y == y - 1 && previous_y->point.x == x)
          {
            node->adj.push_back(previous_y);
            previous_y->adj.push_back(node);
          }
          if(previous_x->point.x == x - 1 && previous_x->point.y == y)
          {
            node->adj.push_back(previous_x);
            previous_x->adj.push_back(node);
          }
          if(y)
          {
            path.pop();
          }
        }
        path.push(node);
      }
      else if(c == '\n')
      {
        x = -1;
        ++y;
      }
    }
    return origin;
}

bool path_finder(string maze) {
  // TODO: Determine whether one can reach the exit at (n - 1, n - 1)
  // starting from (0, 0) in a n × n maze (represented as a string)
  // and return a boolean value accordingly

    Graph* graph = stringToGraph(maze);
    auto size = getMazeSize(maze);

    unordered_set<Graph*> visited;
    stack<Graph*> stack;
    
    stack.push(graph);

    while(!stack.empty())
    {
        Graph* current = stack.top();
        stack.pop();
        
        if(visited.find(current) == visited.end())
        {
            visited.insert(current);
        }
        
        for (auto i = current->adj.begin(); i != current->adj.end(); ++i)
        {
            if(visited.find(*i) == visited.end())
            {
                stack.push(*i);
            }
            
            if((*i)->point.x == size.x && (*i)->point.y == size.y)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cout << (path_finder(".W.\n.W.\n...")?"correct":"incorrect") << endl;
    cout << (path_finder("......\n......\n......\n......\n......\n......")?"correct":"incorrect") << endl;
    cout << (path_finder("...W...\n...W...\n.......\n...W...\n...W...\n...W...")?"correct":"incorrect") << endl;

    cout << (path_finder(".W\nW.")?"incorrect":"correct") << endl;
    cout << (path_finder(".W.\n.W.")?"incorrect":"correct") << endl;
    cout << (path_finder("......\n......\n......\n......\n.....W\n....W.")?"incorrect":"correct") << endl;
    cout << (path_finder(".W....\nW.....\n......\n......\n.....W\n....W.")?"incorrect":"correct") << endl;
    cout << (path_finder("..W...\n..W...\n..W...\n..WW..\n...W..\n...W..")?"incorrect":"correct") << endl;

    return 0;
}