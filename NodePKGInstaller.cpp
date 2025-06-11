#include <bits/stdc++.h>
using namespace std;

class Package
{
public:
    string name;
    vector<string> dependencies;

    Package(string name) : name(name) {}
};

class PackageManager
{
private:
    unordered_map<string, Package *> packages;
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> indegree;

public:
    void addPackage(string name, vector<string> deps)
    {
        if (!packages.count(name))
        {
            packages[name] = new Package(name);
        }
        packages[name]->dependencies = deps;
        for (auto &dep : deps)
        {
            if (!packages.count(dep))
            {
                packages[dep] = new Package(dep);
            }
            graph[dep].push_back(name);
            indegree[name]++;
        }
        if (!indegree.count(name))
        {
            indegree[name] = 0;
        }
    }

    vector<string> getInstallOrder()
    {
        queue<string> q;

        for (auto &[pkg, deg] : indegree)
        {
            if (deg == 0)
            {
                q.push(pkg);
            }
        }

        vector<string> order;

        while (!q.empty())
        {
            string current = q.front();
            order.push_back(current);

            for (auto &neighbour : graph[current])
            {
                indegree[neighbour]--;
                // If indegree becomes 0, add to queue
                if (indegree[neighbour] == 0)
                {
                    q.push(neighbour);
                }
            }
        }

        if (order.size() != packages.size())
        {
            throw runtime_error("Cycle detected or missing dependencies");
        }
        return order;
    }
};

class Installer
{
private:
    PackageManager *packageManager;

public:
    Installer(PackageManager *pm) : packageManager(pm) {}

    void installPackage()
    {
        try
        {
            vector<string> order = packageManager->getInstallOrder();
            cout << "Install Order:\n";

            for (string &pkg : order)
            {
                cout << pkg << endl;
            }
        }
        catch (exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
};

int main()
{
    PackageManager pm;
    pm.addPackage("A", {"B", "C"});
    pm.addPackage("B", {"D"});
    pm.addPackage("C", {"D"});
    pm.addPackage("D", {});

    Installer installer(&pm);
    installer.installPackage();

    return 0;
}