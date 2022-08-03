// 
// 
// 

#include "SingleShot.h"
SingleShot::SingleShot(int aTargetRow, int aTargetCol):m_Row(aTargetRow), m_Col(aTargetCol) {

}

SingleShot::~SingleShot() {

}

int SingleShot::row() {
	return this->m_Row;
}

int SingleShot::col() {
	return this->m_Col;
}