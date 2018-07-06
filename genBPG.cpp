/*
This software is released under the MIT License, see LICENSE.txt.
 */


#include<stdlib.h>
#include<assert.h>
#include<time.h>

#include<iostream>
#include<vector>
#include<deque>


class Graph{
private:
  std::vector<std::vector<int> > adj;
  int n, m;

public:
  Graph(int n, int m, std::vector<std::vector<int> > adj):n(n), m(m), adj(adj) {
  }

  void print(){
    std::cout << "Graph: (n, m) = (" << n << ", " << m << ")" << std::endl; 
    for(int i = 0 ; i<adj.size() ; i++){
      std::cout << i+1 << ": ";
      for(std::vector<int>::iterator itr = adj[i].begin() ; itr != adj[i].end() ; ++itr){
	std::cout << *itr << " ";
      }
      std::cout << std::endl;
    }
  }
};


class Sequence {
private:
  std::vector<int> Seq;
  int numVertices;
  

  void construct(){
    for(int i=0 ; i < 2*numVertices-1 ; i++) Seq[i] = i;
    Seq[2*numVertices -1] = 0;
    randSeq();
    rotate();
  }

  void iterativeConstruction(){
    construct();
    while( !isCanonical() ){
      //std::cerr << "rejection" << std::endl;
      construct();
    }
  }


  void randSeq(){
    for(int i=2*numVertices-2 ; i > 0 ; i--){
      double r=1.0*(i+1)*rand()/RAND_MAX;
      int x=static_cast<int>(r); 
      int tmp=Seq[i];
      Seq[i]=Seq[x];
      Seq[x]=tmp;
    }
    for(int i=0 ; i < 2*numVertices-1 ; i++){
      if(Seq[i] <= numVertices-1) Seq[i]=1;
      else Seq[i]=0;
    }
  }

  bool isValid() const {
    int sum=0;
    for(int i=0 ; i < 2*numVertices-1 ; i++){
      if(Seq[i]==1) sum++;
      else{
	sum--;
	if(sum <= 0) return false;
      }
    }
    //printf("Sequence is valid");
    return true;
  }
  
  void rotate(){
    while(!isValid()){
      int tmp = Seq[0];
      for(int i=0 ; i < 2*numVertices-2 ; i++) Seq[i] = Seq[i+1];
      Seq[2*numVertices-2]=tmp;
    }
  }

  bool isHeavy(std::vector<int> S) const {
    for(int i=0 ; i<2*numVertices ; i++){
      if(S[i]!=Seq[i]){
	if(Seq[i]==0) return false; // not heavy
	else return true; // heavy
      }
    }
    return true; // equal
  }

  std::vector<int> verticalFlip() const {
    std::vector<int> Sj(2*numVertices);
    for(int i=0 ; i<2*numVertices ; i++){
      if(Seq[2*numVertices-i-1]==1) Sj[i]=0;
      else Sj[i]=1;
    }
    return Sj;
  }

  std::vector<int> verticalFlip(std::vector<int> S) const {
    std::vector<int> Sj(2*numVertices);
    for(int i=0 ; i<2*numVertices ; i++){
      if(S[2*numVertices-i-1]==1) Sj[i]=0;
      else Sj[i]=1;
    }
    return Sj;
  }

  
  std::vector<int> holizontalFlip() const {
    std::vector<int> Q = seq2perm();
    std::vector<int> P(numVertices);
    for(int i=0 ; i<numVertices ; i++) P[Q[i]]=i;
    std::vector<int> S = perm2seq(P);
    return S;
  }
  

  std::vector<int> seq2perm() const {
    std::vector<int> Q(numVertices);
    std::deque<int> X, Y;

    for(int i=0 ; i<numVertices ; i++){
      if(Seq[2*i] == 1) X.push_back(i);
      else Y.push_back(i);
    }

    for(int i=0 ; i < numVertices ; i++){
      if(Seq[2*i+1] == 0){
	Q[i] = X.front();
	X.pop_front();
      }
      else{
	Q[i] = Y.front();
	Y.pop_front();
      }
    }
    return Q;
  }

  
  std::vector<int> perm2seq(std::vector<int> P) const {
    assert (P.size() == numVertices);
    
    std::vector<int> S(numVertices*2);
    
    for(int i=0 ; i<numVertices ; i++){
      if(P[i] > i) S[2*i] = 1;
      else S[2*i] = 0;
    }

    int max = 0;
    for(int i=0 ; i<numVertices ; i++){
      if (max < P[i]){
	max = P[i];
	S[2*i+1] = 1;
      }
      else S[2*i+1] = 0;
    }
    
    return S;
  }

  Graph seq2graph() const {
    std::vector<int> perm = seq2perm();
    std::vector<std::vector<int> > adj_list(numVertices, std::vector<int>(0));

    int numEdges = 0;
    for(int i=0 ; i<numVertices ; i++){
      for(int j=i+1 ; j<numVertices ; j++){
	if(perm[i] > perm[j]){
	  adj_list[i].push_back(j+1);
	  adj_list[j].push_back(i+1);
	  numEdges++;
	}
      }
    }
    return Graph(numVertices, numEdges, adj_list);
  }
  

public:
  Sequence(int numVertices):numVertices(numVertices){
    srand ((int) time(NULL));
    Seq.resize(2*numVertices);
    
    iterativeConstruction();
  }

  void reConstruct(){
    iterativeConstruction();
  }

  
  //Check canonical and non-negative
  bool isCanonical() const {
    //non-negative?
    if(!isValid()) return false;
    
    std::vector<int> Sv = verticalFlip();
    std::vector<int> Sh = holizontalFlip();
    std::vector<int> Sr = verticalFlip(Sh);
    
    //Canonical?
    if(!isHeavy(Sv)) return false;
    if(!isHeavy(Sh)) return false;
    if(!isHeavy(Sr)) return false;
    return true;
  }

  std::vector<int> makePermutation() const {
    return seq2perm();
  }

  Graph makeGraph() const {
    return seq2graph();
  }

  void printGraph() const{
    Graph G = seq2graph();
    G.print();
  }

  void printPerm() const {
    std::vector<int> P = seq2perm();
    std::cout << "Permutation: ";
    for(int i=0 ; i<numVertices ; i++){
      std::cout << P[i] << " ";
    }
    std::cout << std::endl;
  }

  
  void print() const {
    for(int i=0 ; i<2*numVertices ; i++){
      if(Seq[i]==1) std::cout << "1";
      else std::cout << "0";
    }
    std::cout << std::endl;
  }
};




int main(int argc, char **argv)
{
  int n;
  
  if(argc < 2){
    std::cout << "Please input an integer: ";
    std::cin >> n;
  }
  else{
    n = atoi(argv[1]);
  }
  
  Sequence S(n);
  S.printPerm();
  S.printGraph();
  
  return 0;
}
