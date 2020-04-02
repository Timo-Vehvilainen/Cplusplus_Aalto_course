#include "ghole.hh"
  
GolfHole::GolfHole(size_t par, size_t hcp) : par(par), hcp(hcp) { }
  
size_t GolfHole::getPar() const {
        return par;
}
  
size_t GolfHole::getHcp() const {
    return hcp;
}
  
std::istream& operator>> (std::istream& in, GolfHole& hole) {
    in >> hole.par >> hole.hcp;
    return in;
}
