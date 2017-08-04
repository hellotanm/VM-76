//=============================================================================
// ■ VMGS/Physics/Physics.cpp
//-----------------------------------------------------------------------------
// Take over the Physics world!
//=============================================================================

#include "Physics.hpp"

PhyEngine::PhyEngine() {

}

bool PhyEngine::AABB(OBB* a, OBB* b) {
	bool collisionX = a->position.x + a->size.x >= b->position.x && b->position.x + b->size.x >= a->position.x;
	bool collisionY = a->position.y + a->size.y >= b->position.y && b->position.y + b->size.y >= a->position.y;
	bool collisionZ = a->position.z + a->size.z >= b->position.z && b->position.z + b->size.z >= a->position.z;
	return collisionX && collisionY && collisionZ;
}

bool BoxCollider::is_collide(BoxCollider* b) {
	OBB aa = {{0.0,0.0,0.0}, {X.length(),Y.length(),Z.length()}};
	glm::vec3 anchor = (w2local * glm::vec4(b->anchor, 1.0));
	glm::vec3 X = glm::mat3(w2local) * glm::vec4(b->X, 1.0);
	glm::vec3 Y = glm::mat3(w2local) * glm::vec4(b->Y, 1.0);
	glm::vec3 Z = glm::mat3(w2local) * glm::vec4(b->Z, 1.0);
	glm::vec3 X2 = X + Y;
	glm::vec3 Z2 = Z + Y;
	glm::vec3 O2 = X + Y + Z;
	glm::vec3 min = glm::min(glm::min(Z2, O2),glm::min(glm::min(Z, X2), glm::min(X, Y)));
	glm::vec3 max = glm::max(glm::max(Z2, O2),glm::max(glm::max(Z, X2), glm::max(X, Y)));
	OBB ab = {min + anchor, max - min};
	bool collision_ab = PhyEngine::AABB(&aa, &ab);
	if (collision_ab) {
		aa = {{0.0,0.0,0.0}, {b->X.length(),b->Y.length(),b->Z.length()}};
		anchor = (b->w2local * glm::vec4(anchor, 1.0));
		X = glm::mat3(b->w2local) * glm::vec4(X, 1.0);
		Y = glm::mat3(b->w2local) * glm::vec4(Y, 1.0);
		Z = glm::mat3(b->w2local) * glm::vec4(Z, 1.0);
		X2 = X + Y;
		Z2 = Z + Y;
		O2 = X + Y + Z;
		min = glm::min(glm::min(Z2, O2),glm::min(glm::min(Z, X2), glm::min(X, Y)));
		max = glm::max(glm::max(Z2, O2),glm::max(glm::max(Z, X2), glm::max(X, Y)));
		ab = {min + anchor, max - min};
		return PhyEngine::AABB(&aa, &ab);
	}
	return false;
}

void BoxCollider::move(glm::vec3 o) {
	anchor = o;
	w2local = glm::lookAt(anchor, anchor + Z, glm::normalize(Y));
}

BoxCollider::BoxCollider(glm::vec3 o, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	anchor = o;
	X = a - o;
	Y = b - o;
	Z = c - o;

	w2local = glm::lookAt(anchor, anchor + Z, glm::normalize(Y));
}
