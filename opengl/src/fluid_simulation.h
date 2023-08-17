#pragma once
struct cell {
	float velocity_x = 0;
	float velocity_y = 0;
	float pressure = 0;
};
class FluidSimulator {
public:
	GLuint textureID;
	int width_of_cells = 0;
	int height_of_cells = 0;
	void createTexture2D()
	{

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set texture parameters (example: linear interpolation)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Allocate storage for the texture (RGBA format, 32-bit floating-point values)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width_of_cells, height_of_cells, 0, GL_RGBA, GL_FLOAT, nullptr);

		// Optionally, you can upload initial data if needed
		// Example: upload initial velocity data (two channels, x and y)
		// std::vector<float> initialData(width * height * 2, 0.0f);
		// glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RG, GL_FLOAT, initialData.data());

		// Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	FluidSimulator(int width, int height) : width_of_cells(width), height_of_cells(height) { createTexture2D();};
	void updateCell(int x, int y, float velocityX, float velocityY, float pressure)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Calculate the index of the texel corresponding to the cell (x, y)
		int texelIndex = y * width_of_cells + x;

		// Update the velocity and pressure values for the texel (cell)
		float texelData[4] = { velocityX, velocityY, pressure, 0.0f };
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 1, 1, GL_RGBA, GL_FLOAT, texelData);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void BindTexture() {
		glBindImageTexture(0, textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	}
};