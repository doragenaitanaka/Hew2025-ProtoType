///**  @file    Collision.cpp
//*    @brief   オブジェクトのサイズを使って当たり判定をとる
//*    @date    2024/12/11
//*    @memo    当たり判定処理についてのサイトからの引用したため完璧な詳細までは記載できないです
//*	 @memo	  英語のコメントは消さずに残しておきます
//*/
//#include "Collision.h"
///**	 @brief   円と円の判定
//*    @param   c1x = 引数1(円)のX座標
//*	 @param   c1y = 引数1(円)のY座標
//*	 @param   c1r = 引数1(円)の半径
//*	 @param   c2x = 引数2(円)のX座標
//*    @param   c2y = 引数2(円)のX座標
//*	 @param   c2r = 引数2(円)の半径
//*    @return  bool 当たり判定が重なっていたらtrueを返す
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
///**	 @brief   円と四角形の判定
//*    @param   cx = 引数1(円)のX座標
//*	 @param   cy = 引数1(円)のY座標
//*	 @param   radius = 引数1(円)の半径
//*	 @param   rx = 引数2(四角形)のX座標
//*    @param   ry = 引数2(四角形)のX座標
//*	 @param   rw = 引数2(四角形)のwidth
//*	 @param   rh = 引数2(四角形)のheight
//*    @return  bool 当たり判定が重なっていたらtrueを返す
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
///**	 @brief   四角形と四角形の判定
//*    @param   r1x = 引数1(四角形)のX座標
//*	 @param   r1y = 引数1(四角形)のY座標
//*	 @param   r1w = 引数1(四角形)のwidth
//*	 @param   r1h = 引数1(四角形)のheight
//*	 @param   r2x = 引数2(四角形)のX座標
//*    @param   r2y = 引数2(四角形)のX座標
//*	 @param   r2w = 引数2(四角形)のwidth
//*	 @param   r2h = 引数2(四角形)のheight
//*    @return  bool 当たり判定が重なっていたらtrueを返す
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
