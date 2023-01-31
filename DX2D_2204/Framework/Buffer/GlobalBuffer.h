#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.matrix = XMMatrixIdentity();//단위행렬
	}

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value);//전치행렬
	}

private:
	struct Data
	{
		Matrix matrix;
	}data;
};

class ColorBuffer : public ConstBuffer
{
public:
	ColorBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.color = { 1, 1, 1, 1 };
	}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		data.color = { r, g, b, a };
	}

	void Set(Float4 color)
	{
		data.color = color;
	}

	Float4& Get() { return data.color; }

private:
	struct Data
	{
		Float4 color;
	}data;
};

class IntValueBuffer : public ConstBuffer
{
public:
	IntValueBuffer() : ConstBuffer(&data, sizeof(Data))
	{		
	}

	struct Data
	{
		int values[4] = {};
	}data;
};

class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer() : ConstBuffer(&data, sizeof(Data))
	{
	}

	struct Data
	{
		float values[4] = {};
	}data;
};