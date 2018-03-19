#include "Parameter.h"

/*!
@brief �p�����[�^�̃Z�b�g
*/
void Parameter::set(std::string key, int val)
{
	_map[key] = val;
}

/*!
@brief �p�����[�^�̎擾
*/
int Parameter::get(std::string key) const
{
	auto it = _map.find(key);   //�w��L�[���擾
	if (_map.end() == it) {     //����������
		return Error;           //�G���[
	}
	else {
		return it->second;      //��������l��Ԃ�
	}
}