#include "Entity.h"
#include "../Core/Libraries.h"

void Entity::allow_accels(bool a){
	has_accels = a;
}

void Entity::allow_accel_x(bool a){

}

void Entity::allow_accel_y(bool a){

}

void Entity::allow_accel_z(bool a){

}

float Entity::get_vel_x(){
	return vel_x;
}

float Entity::get_vel_y(){
	return vel_y;
}

float Entity::get_vel_z(){
	return vel_z;
}

float Entity::get_vel_yaw(){
	return vel_yaw;
}

float Entity::get_vel_pitch(){
	return vel_pitch;
}

float Entity::get_vel_roll(){
	return vel_roll;
}

void Entity::set_vel_x(float n){
	vel_x = n;
}

void Entity::set_vel_y(float n){
	vel_y = n;
}

void Entity::set_vel_z(float n){
	vel_z = n;
}

void Entity::set_vel_yaw(float n){
	vel_yaw = n;
}

void Entity::set_vel_pitch(float n){
	vel_pitch = n;
}

void Entity::set_vel_roll(float n){
	vel_roll = n;
}

//

float Entity::get_accel_x(){
	return accel_x;
}

float Entity::get_accel_y(){
	return accel_y;
}

float Entity::get_accel_z(){
	return accel_z;
}

float Entity::get_accel_yaw(){
	return accel_yaw;
}

float Entity::get_accel_pitch(){
	return accel_pitch;
}

float Entity::get_accel_roll(){
	return accel_roll;
}

void Entity::set_accel_x(float n){
	accel_x = n;
}

void Entity::set_accel_y(float n){
	accel_y = n;
}

void Entity::set_accel_z(float n){
	accel_z = n;
}

void Entity::set_accel_yaw(float n){
	accel_yaw = n;
}

void Entity::set_accel_pitch(float n){
	accel_pitch = n;
}

void Entity::set_accel_roll(float n){
	accel_roll = n;
}

void Entity::pos_update(float delta) {
	float d = static_cast<float> (delta) / 1000;

	_mat_transform = mat_transform;

	_pos_x = pos_x;
	_pos_y = pos_y;
	_pos_z = pos_z;
	_pitch = pos_pitch;
	_yaw = pos_yaw;
	_roll = pos_roll;

	if(has_accels){
		if(has_accel_x) vel_x += accel_x * d;
		if(has_accel_y) vel_y += accel_y * d;
		if(has_accel_z) vel_z += accel_z * d;
		vel_pitch += accel_pitch * d;
		vel_yaw += accel_yaw * d;
		vel_roll += accel_roll * d;
	}
	pos_x += vel_x * d;
	pos_y += vel_y * d;
	pos_z += vel_z * d;
	pos_pitch += vel_pitch * d;
	pos_yaw += vel_yaw * d;
	pos_roll += vel_roll * d;

	if (pos_pitch > 360.0f)
		pos_pitch -= 360.0f;
	else if (pos_pitch < 0.0f)
		pos_pitch += 360.0f;
	if (pos_yaw > 360.0f)
		pos_yaw -= 360.0f;
	else if (pos_yaw < 0.0f)
		pos_yaw += 360.0f;
	if (pos_roll > 360.0f)
		pos_roll -= 360.0f;
	else if (pos_roll < 0.0f)
		pos_roll += 360.0f;

}

bool Entity::does_collide(){
	for(auto &p : verts) {
		for(auto &b : map->get_world_bounds()) {
			if((p->x >= b.x1 && p->x <= b.x2)&&(p->y >= b.y1 && p->y <= b.y2)&&(p->z >= b.z1 && p->z <= b.z2)) return true;
		}
	}
	return false;
}

void Entity::update_verts(){
	mat_transform = mat_rot * mat_translate * mat_scale;
	_vert0 = vert0 * mat_transform,
	_vert1 = vert1 * mat_transform,
	_vert2 = vert2 * mat_transform,
	_vert3 = vert3 * mat_transform,
	_vert4 = vert4 * mat_transform,
	_vert5 = vert5 * mat_transform,
	_vert6 = vert6 * mat_transform,
	_vert7 = vert7 * mat_transform;
}

void Entity::check_collide() {
		build_translate(pos_x, _pos_y, _pos_z);
		update_verts();
		has_accel_x = has_accel_y = has_accel_z = true;
		if(does_collide()) {
			pos_x = _pos_x;
			has_accel_x = false;
		}
		build_translate(_pos_x, pos_y, _pos_z);
		update_verts();
		if(does_collide()) {
			pos_y = _pos_y;
			has_accel_y = false;
		}

		build_translate(_pos_x, _pos_y, pos_z);
		update_verts();
		if(does_collide()) {
			pos_z = _pos_z;
			has_accel_z = false;
		}
}

void Entity::update(float delta) {

	pos_update(delta);
	build_rot(pos_pitch, pos_yaw, pos_roll);
	build_scale(scale_x, scale_y, scale_z);

	check_collide();

	build_translate(pos_x, pos_y, pos_z);
	mat_transform = mat_rot * mat_translate * mat_scale;
	update_verts();

}

void Entity::display(float delta) {
			WorldObject::display(delta);

}
