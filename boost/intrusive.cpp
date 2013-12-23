#include <iostream>
#include <vector>
#include <boost/intrusive_ptr.hpp>

using namespace std;

struct node
{
    typedef boost::intrusive_ptr< node >    ptr_t;

    std::size_t     use_count;

    node() :
        use_count( 0)
    {}

    virtual ~node() {}

    friend inline void intrusive_ptr_add_ref( node * p)
    { ++p->use_count; }

    friend inline void intrusive_ptr_release( node * p)
    { if ( 0 == --p->use_count) delete p; }
};

vector<node::ptr_t> vecx;
vector<node::ptr_t> vecy;

node::ptr_t testfunc() {
    return vecx[0];
}

int main(int argc, char const* argv[])
{
    node::ptr_t x(new node());
    cout << x->use_count << endl;
    node::ptr_t y(x);
    cout << x->use_count << endl;
    cout << y->use_count << endl << endl;
    node::ptr_t z = y;
    cout << x->use_count << endl;
    cout << y->use_count << endl;
    cout << z->use_count << endl << endl;

    vecx.push_back(new node());
    vecx.push_back(x);
    node::ptr_t a = vecx[0];
    cout << vecx[0]->use_count << endl;
    cout << a->use_count << endl << endl;
    cout << x->use_count << endl;
    cout << y->use_count << endl;
    cout << z->use_count << endl << endl;
    vecy.push_back(node::ptr_t(node::ptr_t(new node())));
    cout << vecy[0]->use_count << endl;
    return 0;
}

