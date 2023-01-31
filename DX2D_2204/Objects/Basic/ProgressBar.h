#pragma once

class ProgressBar : public Quad
{
public:
	ProgressBar(wstring frontImageFile, wstring backImageFile, float maxValue);
	~ProgressBar();
		
	void Render();

	void SetValue(float value);

private:
	FloatValueBuffer* valueBuffer;
	Texture* backImage;

	float maxValue;
};