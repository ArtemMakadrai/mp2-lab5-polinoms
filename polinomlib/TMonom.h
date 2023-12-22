#pragma once
struct TMonom
{
	double coef; // коэффициент монома
	int index; // индекс (свертка степеней)


	TMonom() 
	{
		this->coef = 0;
		this->index = 0;
	}

	TMonom(double _coef, int deg) 
	{
		this->coef = _coef;
		this->index = deg;

	}

	void SetCoef(int cval) 
	{
		this->coef = cval;
	}
	int GetCoef(void) 
	{
		return this->coef;
	}

	void SetIndex(int ival) 
	{
		this->index = ival;
	}
	int GetIndex(void) 
	{ 
		return this->index;
	}


	bool operator==(const TMonom& other) 
	{
		if (this->coef == other.coef && this->index == other.index)
			return true;
		else
			return false;
	}
	
	bool operator>(const TMonom& other) 
	{
		if (this->coef <= other.coef) 
			return false;
		else if (this->index <= other.index) 
			return false;
		else 
			return true;
	}

	bool operator<(const TMonom& other) 
	{
		if (this->index >= other.index)
			return false;
		else if (this->coef >= other.coef)
			return false;
		else 
			return true;
	}
	int IMonom() {
		return coef * 1000 + index;
	}



};