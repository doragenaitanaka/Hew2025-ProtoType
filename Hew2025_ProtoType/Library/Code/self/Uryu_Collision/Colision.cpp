///**  @file    Collision.cpp
//*    @brief   �I�u�W�F�N�g�̃T�C�Y���g���ē����蔻����Ƃ�
//*    @date    2024/12/11
//*    @memo    �����蔻�菈���ɂ��ẴT�C�g����̈��p�������ߊ����ȏڍׂ܂ł͋L�ڂł��Ȃ��ł�
//*	 @memo	  �p��̃R�����g�͏������Ɏc���Ă����܂�
//*/
//#include "Collision.h"
///**	 @brief   �~�Ɖ~�̔���
//*    @param   c1x = ����1(�~)��X���W
//*	 @param   c1y = ����1(�~)��Y���W
//*	 @param   c1r = ����1(�~)�̔��a
//*	 @param   c2x = ����2(�~)��X���W
//*    @param   c2y = ����2(�~)��X���W
//*	 @param   c2r = ����2(�~)�̔��a
//*    @return  bool �����蔻�肪�d�Ȃ��Ă�����true��Ԃ�
//*    @date    2024/12/11
//*/
//bool circleCircle(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r) {
//	// get distance between the circle's centers
//	// use the Pythagorean Theorem to compute the distance
//	float distX = c1x - c2x;
//	float distY = c1y - c2y;
//	float distance = sqrt((distX * distX) + (distY * distY));
//
//	// if the distance is less than the sum of the circle's
//	// radii, the circles are touching!
//	if (distance <= c1r + c2r) {
//		return true;
//	}
//	return false;
//}
//
///**	 @brief   �~�Ǝl�p�`�̔���
//*    @param   cx = ����1(�~)��X���W
//*	 @param   cy = ����1(�~)��Y���W
//*	 @param   radius = ����1(�~)�̔��a
//*	 @param   rx = ����2(�l�p�`)��X���W
//*    @param   ry = ����2(�l�p�`)��X���W
//*	 @param   rw = ����2(�l�p�`)��width
//*	 @param   rh = ����2(�l�p�`)��height
//*    @return  bool �����蔻�肪�d�Ȃ��Ă�����true��Ԃ�
//*    @date    2024/12/11
//*/
//bool circleRect(float cx, float cy, float radius, float rx, float ry, float rw, float rh) {
//
//
//	// temporary variables to set edges for testing
//	float testX = cx;
//	float testY = cy;
//
//	// which edge is closest?
//	if (cx < rx)         testX = rx;      // test left edge
//	else if (cx > rx + rw) testX = rx + rw;   // right edge
//	if (cy < ry)         testY = ry;      // top edge
//	else if (cy > ry + rh) testY = ry + rh;   // bottom edge
//
//	// get distance from closest edges
//	float distX = cx - testX;
//	float distY = cy - testY;
//	float distance = sqrt((distX * distX) + (distY * distY));
//
//	// if the distance is less than the radius, collision!
//	if (distance <= radius) {
//		return true;
//	}
//	return false;
//}
//
///**	 @brief   �l�p�`�Ǝl�p�`�̔���
//*    @param   r1x = ����1(�l�p�`)��X���W
//*	 @param   r1y = ����1(�l�p�`)��Y���W
//*	 @param   r1w = ����1(�l�p�`)��width
//*	 @param   r1h = ����1(�l�p�`)��height
//*	 @param   r2x = ����2(�l�p�`)��X���W
//*    @param   r2y = ����2(�l�p�`)��X���W
//*	 @param   r2w = ����2(�l�p�`)��width
//*	 @param   r2h = ����2(�l�p�`)��height
//*    @return  bool �����蔻�肪�d�Ȃ��Ă�����true��Ԃ�
//*    @date    2024/12/11
//*/
//bool rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h) {
//
//	// are the sides of one rectangle touching the other?
//
//	if (r1x + r1w >= r2x &&    // r1 right edge past r2 left
//		r1x <= r2x + r2w &&    // r1 left edge past r2 right
//		r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
//		r1y <= r2y + r2h) {    // r1 bottom edge past r2 top
//		return true;
//	}
//	return false;
//}