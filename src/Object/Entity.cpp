#include "Entity.h"

#include "../Core/Dependancies/Libraries.h"

void Entity::allow_accels(bool a){
	has_accels = a;
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
	_mat_transform = mat_transform;

	_pos_x = pos_x;
	_pos_y = pos_y;
	_pos_z = pos_z;
	_pos_pitch = pos_pitch;
	_pos_yaw = pos_yaw;
	_pos_roll = pos_roll;
	_vel_x = vel_x;
	_vel_y = vel_y;
	_vel_z = vel_z;
	_vel_yaw = vel_yaw;
	_vel_pitch = vel_pitch;
	_vel_roll = vel_roll;

	if(has_accels){
		if(has_accel_x) vel_x += accel_x * delta;
		if(has_accel_y) vel_y += accel_y * delta;
		if(has_accel_z) vel_z += accel_z * delta;
		if(has_accel_pitch) vel_pitch += accel_pitch * delta;
		if(has_accel_yaw) vel_yaw += accel_yaw * delta;
		if(has_accel_roll) vel_roll += accel_roll * delta;
	}

	if (vel_x > 53.0f)
		vel_x = 53.0f;
	else if(vel_x < -53.0f)
		vel_x = -53.0f;
	if (vel_y > 53.0f)
		vel_y = 53.0f;
	else if(vel_y < -53.0f)
		vel_y = -53.0f;
	if (vel_z > 53.0f)
		vel_z = 53.0f;
	else if(vel_z < -53.0f)
		vel_z = -53.0f;

	pos_x += vel_x * delta;
	pos_y += vel_y * delta;
	pos_z += vel_z * delta;
	pos_pitch += vel_pitch * delta;
	pos_yaw += vel_yaw * delta;
	pos_roll += vel_roll * delta;

	if (pos_pitch > 2*PI)
		pos_pitch -= 2*PI;
	else if (pos_pitch < 0.0f)
		pos_pitch += 2*PI;
	if (pos_yaw > 2*PI)
		pos_yaw -= 2*PI;
	else if (pos_yaw < 0.0f)
		pos_yaw += 2*PI;
	if (pos_roll > 2*PI)
		pos_roll -= 2*PI;
	else if (pos_roll < 0.0f)
		pos_roll += 2*PI;

}

bool Entity::does_collide(){
	float x_max, x_min, y_max, y_min, z_max, z_min;
	bool flag = true;
	for(auto p : bb_verts) {
		if(flag) {
			x_max = p.x;
			x_min = p.x;
			y_max = p.y;
			y_min = p.y;
			z_max = p.z;
			z_min = p.z;
			flag = false;
		}
		if(p.x > x_max) x_max = p.x;
		else if(p.x < x_min) x_min = p.x;
		if(p.y > y_max) y_max = p.y;
		else if(p.y < y_min) y_min = p.y;
		if(p.z > z_max) z_max = p.z;
		else if(p.z < z_min) z_min = p.z;
	}
	for(auto b : map->get_world_bounds()) {
		if((x_min <= b.x1 && x_max >= b.x2)&&(y_min <= b.y1 && y_max >= b.y2)&&(z_min <= b.z1 && z_max >= b.z2)) return true;
	}
	return false;
}


void Entity::check_collide() {
		has_accel_x = has_accel_y = has_accel_z = has_accel_pitch = has_accel_yaw = has_accel_roll = true;

		build_rot(pos_pitch, _pos_yaw, _pos_roll);
		update_verts(bb_verts, bbverts);
		if(does_collide()) {
			//pos_pitch = _pos_pitch;
			vel_pitch = 0;
			has_accel_pitch = false;
		}

		build_rot(_pos_pitch, pos_yaw, _pos_roll);
		update_verts(bb_verts, bbverts);
		if(does_collide()) {
			//pos_yaw = _pos_yaw;
			vel_yaw = 0;
			has_accel_yaw = false;
		}

		build_rot(_pos_pitch, _pos_yaw, pos_roll);
		update_verts(bb_verts, bbverts);
		if(does_collide()) {
			//pos_roll = _pos_roll;
			vel_roll = 0;
			has_accel_roll = false;
		}

		build_translate(pos_x, _pos_y, _pos_z);

		update_verts(bb_verts, bbverts);
		if(does_collide()) {
			pos_x = _pos_x;
			vel_x = 0;
			has_accel_x = false;
		}

		build_translate(_pos_x, pos_y, _pos_z);
		update_verts(bb_verts, bbverts);
		if(does_collide()) {
			pos_y = _pos_y;
			vel_y = 0;
			has_accel_y = false;
		}

		build_translate(_pos_x, _pos_y, pos_z);
		update_verts(bb_verts, bbverts);
		if(does_collide()) {
			pos_z = _pos_z;
			vel_z = 0;
			has_accel_z = false;
		}
}

void Entity::update(float delta) {
	pos_update(delta);
	build_scale(scale_x, scale_y, scale_z);
	check_collide();
	WorldObject::update(delta);

}

void Entity::display(float delta, GameManager & manager) {
			WorldObject::display(delta, manager);
}
