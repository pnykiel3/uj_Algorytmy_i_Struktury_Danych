#include <fstream>
#include <cstdlib>

template <int capacity>
class ADTgraph {
  int vertices[capacity];
  int edges[capacity][capacity];
  int size;


  public:
  ADTgraph() {
        size = 0;
        for (int i = 0; i < capacity; i++) {
            vertices[i] = 0;
            for (int j = 0; j < capacity; j++) {
                edges[i][j] = 0;
            }
        }
    }
    
   ~ADTgraph() {
        for (int i = 0; i < capacity; i++) {
            vertices[i] = 0;
            for (int j = 0; j < capacity; j++) {
                edges[i][j] = 0;
            }
        }
    }
    
  bool adjacent(int u, int v) {
        return edges[u][v];
    }

  int* neighbors(int v) {
      int a = 0;
      for (int i = 0; i < capacity; i++) {
          if (vertices[i]) a++;
      }

      int* n = new int[a];

      for (int i = 0, a = 0; i < capacity; i++) {
          if (edges[v][i]) {
              n[a] = i;
              a++;
          }
      }

      n[a] = 0;
      return n;
  }

  void addVertex(int v) {
        vertices[v] = 1;
        size++;
    }

  void removeVertex(int v) {
        vertices[v] = 0;
        for (int i = 0; i < capacity; i++) {
            edges[v][i] = 0;
            edges[i][v] = 0;
        }
        size--;
    }

  void addEdge(int u, int v) {
        if ( vertices[u] && vertices[v] ) edges[u][v] = 1;

    }

  void removeEdge(int u, int v) {
        edges[u][v] = 0;
    }

  int getVertexValue(int v) {
      return vertices[v];
  }

  void setVertexValue(int v, int val) {
        vertices[v] = val;
    }

  int getEdgeValue(int u, int v) {
      return edges[u][v];
  }

  void setEdgeValue(int u, int v, int val) {
        if (vertices[u] && vertices[v]) edges[u][v] = val;
    }

  int getSize() {
        return size;
    }

    void print(std::string filename) {
        std::ofstream out;
        out.open(filename + ".txt");
        if (!out) {
            std::cerr << "Błąd otwarcia pliku do zapisu.\n";
            return;
        }
        out << "digraph G {" << std::endl;
        for (int i =0; i < capacity; i++){
            for (int j = 0; j < capacity; j++){
                if (edges[i][j]){
                    out << i << " -> " << j << std::endl;
                }
            }
        }
        out << "}" << std::endl;
        out.close();
        std::string cmd = "dot -Tpng " + filename + ".txt -o " + filename + ".jpg";
        system(cmd.c_str());

    }

};