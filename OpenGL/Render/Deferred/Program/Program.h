#pragma once

#include "../../Util/common.h"

class CShader;

class VSProgram
{
protected:
	CShader* m_pShader;
	ullong parameter;

private:
	std::string m_programName;

public:
	VSProgram();
	~VSProgram();

	std::string GetName() const { return m_programName; }

};

