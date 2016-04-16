#ifndef _MIDEND_REMOVERETURNS_H_
#define _MIDEND_REMOVERETURNS_H_

#include "ir/ir.h"
#include "frontends/common/resolveReferences/resolveReferences.h"

namespace P4 {

// This replaces 'returns' and/or 'exits' by ifs
class RemoveReturns : public Transform {
    P4::ReferenceMap* refMap;
    bool              removeReturns;  // if true remote returns, else remove exits
    IR::ID            returnVar;  // one for each context

    std::vector<bool> stack;
    void push() { stack.push_back(false); }
    void pop() { stack.pop_back(); }
    void setReturned() { stack.back() = true; }
    bool mayHaveReturned() { return stack.back(); }
 public:
    RemoveReturns(P4::ReferenceMap* refMap, bool removeReturns = true) :
            refMap(refMap), removeReturns(removeReturns) {}

    const IR::Node* preorder(IR::BlockStatement* statement) override;
    const IR::Node* preorder(IR::ReturnStatement* statement) override;
    const IR::Node* preorder(IR::ExitStatement* statement) override;
    const IR::Node* preorder(IR::IfStatement* statement) override;
    const IR::Node* preorder(IR::SwitchStatement* statement) override;

    const IR::Node* preorder(IR::P4Action* action) override;
    const IR::Node* preorder(IR::P4Control* control) override;
};

}  // namespace P4

#endif /* _MIDEND_REMOVERETURNS_H_ */
