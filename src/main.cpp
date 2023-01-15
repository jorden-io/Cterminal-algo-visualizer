#include <iostream>
#include <unistd.h>
#include <vector>
class node
{
public:
    int val{0};
    node *up{};
    node *down{};
    node *right{};
    node *left{};
};
template <class T, int i_rows, int i_cols>
class graph
{
public:
    int rows{i_rows};
    int cols{i_cols};
    node v[i_cols][i_rows]{};
    graph()
    {
        for (int i = 0; i < i_rows; i++)
        {
            for (int j = 0; j < i_cols; j++)
            {
                v[j][i].val = 0;
                if (j >= 1)
                {
                    if (&v[i][j - 1])
                    {
                        v[j][i].up = &v[j][i - 1];
                        v[j][i].down = &v[j][i + 1];
                        v[j][i].right = &v[j + 1][i];
                        v[j][i].left = &v[j - 1][i];
                    };
                };
            };
        };
    };
    ~graph(){};
    T &operator[](T i)
    {
        return v[i];
    };
    friend std::ostream &operator<<(std::ostream &out, graph<T, i_rows, i_cols> &g)
    {
        for (int i = 0; i < g.rows; i++)
        {
            out << "\n";
            for (int j = 0; j < g.cols; j++)
            {
                std::cout << g.v[j][i].val;
            };
        };
        return out;
    };
};
void find_path(graph<node, 25, 50> &graph, int sx, int sy, int dx, int dy)
{
    int moves{0};
    graph.v[sx][sy].val = 0;
    for (int i = 0; i < (dx - dy); i++)
    {
        if (dy > sy)
        {
            moves++;
            if (!(moves > (dy - sy + 1)))
            {
                graph.v[sx][sy + i].val = 0;
            };
            if (moves > (dy - sy))
            {
                if (moves < (dx - sx))
                {
                    int re{0};
                re:
                    re++;
                    if (re < (dx - sx + 1))
                    {
                        usleep(100000);
                        std::cout << graph;
                        graph.v[sx + re][sy + (dy - sy)].val = 0;
                        goto re;
                    };
                    return;
                };
                if (moves > 10)
                {
                    return;
                };
            };
        };

        // if (dy > sy)
        // {
        //     moves++;
        //     if (!(moves > (dy - sy + 1)))
        //     {
        //         graph.v[sx][sy + i].val = 0;
        //     };
        //     if (moves > (dy - sy))
        //     {
        //         if (moves < (dx - sx))
        //         {
        //             int re{0};
        //         re:
        //             re++;
        //             if (re < (dx - sx + 1))
        //             {
        //                 usleep(100000);
        //                 std::cout << graph;
        //                 graph.v[sx + re][sy + (dy - sy)].val = 0;
        //                 goto re;
        //             };
        //             return;
        //         };
        //         if (moves > 10)
        //         {
        //             return;
        //         };
        //     };
        // };

        usleep(100000);
        std::cout << graph;
    };
    return;
};
void breath_first_find(int startr, int startc, int desr, int desc, graph<node, 25, 50> &graph)
{
    graph.v[desr][desc].val = 5;
    std::vector<node> queue{};
    queue.push_back(graph.v[startr][startc]);
    while (queue.size() > 0)
    {
        usleep(10000);
        node current = queue.front();
        if (current.val == graph.v[desr][desc].val || current.right->val == graph.v[desr][desc].val || current.left->val == graph.v[desr][desc].val || current.up->val == graph.v[desr][desc].val || current.down->val == graph.v[desr][desc].val)
        {
            find_path(graph, startr, startc, desr, desc);
            std::cout << "\nfound node: (x-" << desr << " y-" << desc << ")\n";
            std::cout << "shortest path: " << (desc - startc) << "-down " << (desr - startr) << "-right\n";
            return;
        };
        current.val = 0;
        if (current.left->val == 0)
        {
            if (current.left->left)
            {
                queue.push_back(*current.left);
            };
            current.left->val = 1;
        };
        if (current.up->val == 0)
        {
            if (current.up->up)
            {
                queue.push_back(*current.up);
            };
            current.up->val = 1;
        };
        if (current.right->val == 0)
        {
            if (current.right->right)
            {
                queue.push_back(*current.right);
            };
            current.right->val = 1;
        };
        if (current.down->val == 0)
        {
            if (current.down->down)
            {
                queue.push_back(*current.down);
            };
            current.down->val = 1;
        };
        queue.erase(queue.begin());
        std::cout << graph;
    };
};
int main(int argc, char *argv[])
{
    graph<node, 25, 50> graph{};
    breath_first_find(20, 11, 35, 15, graph);
    return 0;
};