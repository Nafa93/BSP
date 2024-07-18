#include "Node.h"

bool Node::has_children() {
	return left != nullptr && right != nullptr;
}