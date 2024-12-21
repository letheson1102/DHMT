#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <glew.h>
#include <freeglut.h>

#include <vector_matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	 -0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int
CurrentWidth = 1080,
CurrentHeight = 1080;

bool
translated = false,
rotated = false,
scaled = false,
otoxoay = false;

mat4
projection_mat_cpp;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };

int
projection_mat_location;


bool light1Enabled = false;


class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

MatrixStack  mvstack;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4 model_mat_cpp;
int model_mat_location;

mat4 view_mat_cpp;
int view_mat_location;

float alphaQuat = 0.0f;
float alcanGat = 0.0f;
float alcuaSo = 0.0f;
float alcamera = 0.0f;
float otodichuyen = 0.0f;
float otodichuyen2 = 0.0f;
float cuakinhxebus = 0.0f;
float xebusdichuyen = 0.0f;

// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);

}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

// ---------------------------------------------------------------------------	
void MATDAT()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();

	// Giảm chiều dày để vỉa hè trông tự nhiên hơn
	instance = model_mat_cpp * scale(vec3(1.5f, 0.02f, 1.0f));  // Cải thiện chiều dày vỉa hè
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6f, 0.6f, 0.6f, 1.0f);  // Màu xám xi măng

	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}


void KERDUONGDI()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, 1.0f);  // Màu trắng cho đường kẻ

	float lane_width = 0.04f;  // Độ rộng của mỗi đường kẻ
	float lane_length = 0.08f;  // Độ dài của mỗi đường kẻ
	int num_lanes = 5;          // Số lượng đường kẻ (không thay đổi)
	float lane_spacing = -0.5f; // Khoảng cách giữa các đường kẻ

	for (int i = 0; i < num_lanes; ++i) {
		mvstack.push(model_mat_cpp);
		lane_spacing += 0.17f;

		// Dịch chuyển từng đường kẻ theo trục x và z
		model_mat_cpp = model_mat_cpp * translate(vec3(-0.5f, 0.012f, lane_spacing)); // Dịch 0.5 theo trục X
		instance = model_mat_cpp * scale(vec3(lane_width, 0.001f, lane_length));

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	model_mat_cpp = mvstack.pop();
}

void CONDUONG()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);  // Màu xám cho con đường

	float road_width = 0.4f;  // Độ rộng của con đường
	float road_length = 1.0f; // Độ dài của con đường

	// Dịch chuyển con đường 0.5 theo trục X và 0.01 theo trục Y
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.5f, 0.011f, 0.0f)); // Dịch 0.5 theo trục X
	instance = model_mat_cpp * scale(vec3(road_width, 0.001f, road_length));

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void VIAHE()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.7f, 1.0f);  // Màu xám nhạt cho vỉa hè

	float road_width = 0.8f;  // Độ rộng của con đường
	float road_length = 1.0f; // Độ dài của con đường

	// Dịch chuyển con đường 0.5 theo trục X và 0.01 theo trục Y
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.5f, 0.01f, 0.0f)); // Dịch 0.5 theo trục X
	instance = model_mat_cpp * scale(vec3(road_width, 0.001f, road_length));

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void DENDUONG(float x, float z)
{
    mvstack.push(model_mat_cpp);

    // Thân đèn (hình trụ dọc)
    float pole_height = 0.15f;   // Chiều cao thân đèn
    float pole_radius = 0.01f;   // Bán kính thân đèn
    model_mat_cpp = model_mat_cpp * translate(vec3(x, pole_height / 2, z)); // Đặt thân đèn
    mat4 instance = model_mat_cpp * scale(vec3(pole_radius, pole_height, pole_radius));
    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

    GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
    glUniform4f(colorLocation, 0.3f, 0.3f, 0.3f, 1.0f); // Màu xám cho thân đèn
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Thêm đế đèn (hình tròn phẳng dưới cùng)
    model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, -pole_height / 2, 0.0f)); // Đặt đế đèn dưới thân
    instance = model_mat_cpp * scale(vec3(0.02f, 0.005f, 0.02f)); // Kích thước nhỏ cho đế đèn
    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
    glUniform4f(colorLocation, 0.2f, 0.2f, 0.2f, 1.0f); // Màu xám tối cho đế đèn
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Chụp đèn (hình hộp nhỏ trên đỉnh)
    model_mat_cpp = model_mat_cpp * translate(vec3(0.0f,0.1f + pole_height / 2, 0.0f)); // Đỉnh thân đèn
    instance = model_mat_cpp * scale(vec3(0.04f, 0.04f, 0.04f));  // Kích thước chụp đèn
    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

    
	if (light1Enabled) {
		glUniform4f(colorLocation, 1.0f, 1.0f, 0.8f, 1.0f); // Màu vàng nhạt cho chụp đèn
	}
	else
	{
		glUniform4f(colorLocation, 0.2f, 0.2f, 0.1f, 1.0f); // Màu vàng nhạt cho bóng đèn
	}
    glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 0.05f, 0.0f));
	for (int i = 0; i <= 360; i+=10) {
		for (int j = 0; j <= 360; j += 10) {
			// Bóng đèn (hình cầu)
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút
			instance = model_mat_cpp * scale(vec3(0.04, 0.04, 0.04));  // Kích thước bóng đèn
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
			if (light1Enabled) {
				glUniform4f(colorLocation, 1.0f, 1.0f, 0.5f, 1.0f); // Màu vàng nhạt cho bóng đèn
			}
			else
			{
				glUniform4f(colorLocation, 0.4f, 0.4f, 0.15f, 1.0f); // Màu vàng nhạt cho bóng đèn
			}
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
    model_mat_cpp = mvstack.pop();
}


void CAYCOI(float x, float z)
{
	mvstack.push(model_mat_cpp);

	// Thân cây (hình trụ dọc)
	float trunk_height = 0.15f;   // Chiều cao thân cây
	float trunk_radius = 0.01f;   // Bán kính thân cây
	model_mat_cpp = model_mat_cpp * translate(vec3(x, trunk_height / 2, z)); // Đặt thân cây
	mat4 instance = model_mat_cpp * scale(vec3(trunk_radius, trunk_height, trunk_radius));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.4f, 0.25f, 0.1f, 1.0f); // Màu nâu cho thân cây
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Tán cây (hình cầu trên đỉnh)
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, trunk_height / 2, 0.0f)); // Đỉnh thân cây


	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút

			// Bóng đèn (hình cầu)
			instance = model_mat_cpp * scale(vec3(0.05f, 0.05f, 0.05f));  // Tán cây dạng cầu
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

			glUniform4f(colorLocation, 0.1f, 0.6f, 0.2f, 1.0f); // Màu xanh lá cho tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	// Chi tiết tán cây: chia tán thành nhiều phần nhỏ hơn (các hình cầu)
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.03f, 0.02f, 0.0f)); // Đẩy lại một chút để tránh tán cây bị nâng cao


	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			// Bóng đèn (hình cầu)
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút

			instance = model_mat_cpp * scale(vec3(0.03f, 0.03f, 0.03f));
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
			glUniform4f(colorLocation, 0.1f, 0.7f, 0.3f, 1.0f); // Màu xanh lá sáng cho các phần nhỏ của tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	// Thêm nhiều phần cho tán cây: Lặp lại với nhiều vị trí và kích thước khác nhau
	model_mat_cpp = model_mat_cpp * translate(vec3(0.06f, 0.0f, 0.0f)); // Dịch ra ngoài một chút (chỉnh lại trục y)


	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			// Bóng đèn (hình cầu)
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút

			instance = model_mat_cpp * scale(vec3(0.04f, 0.04f, 0.04f)); // Tăng kích thước cho một phần khác
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
			glUniform4f(colorLocation, 0.1f, 0.5f, 0.2f, 1.0f); // Màu xanh lá khác cho các phần của tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	// Thêm một số phần nhỏ khác để tán cây trông tự nhiên hơn
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.05f, 0.01f, 0.05f)); // Dịch ra ngoài một chút (tránh nâng cao quá mức)
	for (int i = 0; i <= 360; i += 10) {
		for (int j = 0; j <= 360; j += 10) {
			// Bóng đèn (hình cầu)
			model_mat_cpp = model_mat_cpp * rotate_y(j) * rotate_z(i); // Đẩy bóng đèn lên một chút
			instance = model_mat_cpp * scale(vec3(0.03f, 0.03f, 0.03f));
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
			glUniform4f(colorLocation, 0.2f, 0.6f, 0.2f, 1.0f); // Một màu khác cho tán cây
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
	}

	model_mat_cpp = mvstack.pop();
}


void VEDUONGDI()
{
	 //Đèn đường bên trái
	float z = -0.5f;
	for (int i = 0; i < 5; ++i) {
		z += 0.17f; // Khoảng cách giữa các đèn
		DENDUONG(-0.75f, z); // Đèn cách trục đường bên trái
	}

	//Đèn đường bên trái
	float zh = -0.5f;
	for (int i = 0; i < 5; ++i) {
		zh += 0.17f; // Khoảng cách giữa các đèn
		CAYCOI(-0.25f, zh); // Đèn cách trục đường bên trái
	}

}
void THUNGRAC(float x, float z)
{
	mvstack.push(model_mat_cpp);

	// Thân thùng (hình trụ dọc)
	float can_height = 0.1f;  // Chiều cao thân thùng
	float can_radius = 0.05f; // Bán kính thân thùng
	model_mat_cpp = model_mat_cpp * translate(vec3(x, can_height / 2, z)); // Đặt thân thùng
	mat4 instance = scale(vec3(can_radius, can_height, can_radius)); // Kích thước thân thùng
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.0f, 0.4f, 1.0f); // Màu đỏ thẫm cho thân thùng
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Nắp thùng (hình tròn)
	mvstack.push(model_mat_cpp); // Lưu lại trạng thái trước khi xử lý nắp thùng
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, can_height / 2, 0.0f)); // Đỉnh thân thùng

	// Quay nắp thùng (căn chỉnh trục)
	mat4 translation_to_origin = translate(vec3(0.0f, -can_height / 2, 0.0f)); // Dịch về trục quay
	mat4 rotation = rotate_x(45.0f); // Quay 45 độ quanh trục X
	mat4 translation_back = translate(vec3(0.0f, can_height / 2, 0.0f)); // Dịch lại vị trí ban đầu

	model_mat_cpp = model_mat_cpp * translation_to_origin * rotation * translation_back; // Kết hợp các phép biến đổi

	instance = scale(vec3(can_radius * 1.1f, 0.01f, can_radius * 1.1f)); // Nắp lớn hơn một chút
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.5f, 0.3f, 0.3f, 1.0f); // Màu đỏ thẫm cho nắp thùng
	glDrawArrays(GL_TRIANGLES, 0, 36);

	mvstack.pop(); // Khôi phục trạng thái trước khi xử lý nắp thùng
	model_mat_cpp = mvstack.pop(); // Khôi phục trạng thái toàn bộ
}

void XEOTO(float x, float z)
{
	mvstack.push(model_mat_cpp);

	// Thân xe (hình hộp)
	float car_length = 0.15f;  // Chiều dài xe
	float car_width = 0.08f;   // Chiều rộng xe
	float car_height = 0.04f;  // Chiều cao xe
	model_mat_cpp = model_mat_cpp * translate(vec3(x, car_height / 2 + 0.02f, z)) * rotate_y(-90.0f); // Đặt vị trí cho thân xe
	mat4 instance = scale(vec3(car_length, car_height, car_width)); // Tạo hình hộp cho thân xe
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f); // Màu xanh lam cho thân xe
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Bánh xe (hình trụ)
	float wheel_radius = 0.015f; // Bán kính bánh xe (tăng 50%)
	float wheel_width = 0.025f; // Bề rộng bánh xe (tăng 50%)

	// Tọa độ tương đối của các bánh xe so với thân xe
	vec3 wheel_positions[4] = {
		vec3(car_length / 4, -car_height / 2, car_width / 2),   // Bánh trước bên phải
		vec3(car_length / 4, -car_height / 2, -car_width / 2),  // Bánh trước bên trái
		vec3(-car_length / 4, -car_height / 2, car_width / 2),  // Bánh sau bên phải
		vec3(-car_length / 4, -car_height / 2, -car_width / 2)  // Bánh sau bên trái
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 360; j += 20) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(wheel_positions[i]) * rotate_z(j); // Đặt vị trí bánh xe
			instance = scale(vec3(wheel_radius, wheel_width, wheel_radius)); // Tạo kích thước bánh xe lớn hơn
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
			glUniform4f(colorLocation, 0.1f, 0.1f, 0.1f, 1.0f); // Màu đen cho bánh xe
			glDrawArrays(GL_TRIANGLES, 0, 36);
			model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó
		}

	}


	// Thêm phần mui xe (nhô lên giữa xe)
	mvstack.push(model_mat_cpp);
	float roof_height = 0.025f;  // Chiều cao mui xe
	float roof_length = 0.08f;  // Chiều dài mui xe
	float roof_width = 0.07f;   // Chiều rộng mui xe
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, car_height / 2 + roof_height / 2, 0.0f)); // Vị trí mui xe
	instance = scale(vec3(roof_length, roof_height, roof_width)); // Kích thước mui xe
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.9f, 0.9f, 0.9f, 1.0f); // Màu bạc cho mui xe
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Thêm kính chắn gió (nhô lên)
	mvstack.push(model_mat_cpp);
	float windshield_height = 0.015f;  // Chiều cao kính chắn gió
	float windshield_length = 0.07f;  // Chiều dài kính chắn gió
	float windshield_width = 0.05f;   // Chiều rộng kính chắn gió
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.01f, car_height / 2 + windshield_height / 2, 0.0f)); // Vị trí kính chắn gió
	instance = scale(vec3(windshield_length, windshield_height, windshield_width)); // Kích thước kính chắn gió
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.6f, 0.8f, 0.6f, 1.0f); // Màu kính (xanh lá nhạt)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	model_mat_cpp = mvstack.pop();
}

void XEOTO_DO(float x, float z)
{
	mvstack.push(model_mat_cpp);

	// Thân xe (hình hộp)
	float car_length = 0.15f;  // Chiều dài xe
	float car_width = 0.08f;   // Chiều rộng xe
	float car_height = 0.04f;  // Chiều cao xe
	model_mat_cpp = model_mat_cpp * translate(vec3(x, car_height / 2 + 0.02, z)) * rotate_y(-90.0f); // Đặt vị trí cho thân xe
	mat4 instance = scale(vec3(car_length, car_height, car_width)); // Tạo hình hộp cho thân xe
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.2f, 0.2f, 1.0f); // Màu xanh lam cho thân xe
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Bánh xe (hình trụ)
	float wheel_radius = 0.015f; // Bán kính bánh xe (tăng 50%)
	float wheel_width = 0.025f; // Bề rộng bánh xe (tăng 50%)

	// Tọa độ tương đối của các bánh xe so với thân xe
	vec3 wheel_positions[4] = {
		vec3(car_length / 4, -car_height / 2, car_width / 2),   // Bánh trước bên phải
		vec3(car_length / 4, -car_height / 2, -car_width / 2),  // Bánh trước bên trái
		vec3(-car_length / 4, -car_height / 2, car_width / 2),  // Bánh sau bên phải
		vec3(-car_length / 4, -car_height / 2, -car_width / 2)  // Bánh sau bên trái
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 360; j += 20) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(wheel_positions[i]) * rotate_z(j); // Đặt vị trí bánh xe
			instance = scale(vec3(wheel_radius, wheel_width, wheel_radius)); // Tạo kích thước bánh xe lớn hơn
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
			glUniform4f(colorLocation, 0.1f, 0.1f, 0.1f, 1.0f); // Màu đen cho bánh xe
			glDrawArrays(GL_TRIANGLES, 0, 36);
			model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó
		}

	}


	// Thêm phần mui xe (nhô lên giữa xe)
	mvstack.push(model_mat_cpp);
	float roof_height = 0.025f;  // Chiều cao mui xe
	float roof_length = 0.08f;  // Chiều dài mui xe
	float roof_width = 0.07f;   // Chiều rộng mui xe
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, car_height / 2 + roof_height / 2, 0.0f)); // Vị trí mui xe
	instance = scale(vec3(roof_length, roof_height, roof_width)); // Kích thước mui xe
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.9f, 0.9f, 0.9f, 1.0f); // Màu bạc cho mui xe
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Thêm kính chắn gió (nhô lên)
	mvstack.push(model_mat_cpp);
	float windshield_height = 0.015f;  // Chiều cao kính chắn gió
	float windshield_length = 0.07f;  // Chiều dài kính chắn gió
	float windshield_width = 0.05f;   // Chiều rộng kính chắn gió
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.01f, car_height / 2 + windshield_height / 2, 0.0f)); // Vị trí kính chắn gió
	instance = scale(vec3(windshield_length, windshield_height, windshield_width)); // Kích thước kính chắn gió
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.6f, 0.8f, 0.6f, 1.0f); // Màu kính (xanh lá nhạt)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	model_mat_cpp = mvstack.pop();
}

float scale_factor = 30.0f;

void duiQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.2f / scale_factor, 0.5f / scale_factor, 1.2f / scale_factor)) * translate(vec3(0.0, 13.9 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.5f, 0.1f, 1.0f); // Màu xám nhạt
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void trucQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.2f / scale_factor, 2.0f / scale_factor, 0.2f / scale_factor)) * translate(vec3(0.0, -0.4f / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.7f, 0.3f, 0.3f, 1.0f); // Màu đỏ nhạt
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tamQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.9f / scale_factor, 0.2f / scale_factor, 0.9f / scale_factor)) * translate(vec3(0.0, 24.5 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.8f, 0.2f, 1.0f); // Màu xanh lá cây
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(4.0f / scale_factor, 0.15f / scale_factor, 0.7f / scale_factor)) * translate(vec3(0.6 / scale_factor, 32.5 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.3f, 0.3f, 0.8f, 1.0f); // Màu xanh lam
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(4.0f / scale_factor, 0.15f / scale_factor, 0.7f / scale_factor)) * translate(vec3(-0.6 / scale_factor, 32.5 / scale_factor, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.3f, 0.3f, 0.8f, 1.0f); // Màu xanh lam
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.7f / scale_factor, 0.15f / scale_factor, 4.0f / scale_factor)) * translate(vec3(0.0, 32.5 / scale_factor, 0.0)) * rotate_y(90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.3f, 0.3f, 0.8f, 1.0f); // Màu xanh lam

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.7f / scale_factor, 0.15f / scale_factor, 4.0f / scale_factor)) * translate(vec3(0.0, 32.5 / scale_factor, 0.0)) * rotate_y(-90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.3f, 0.3f, 0.8f, 1.0f); // Màu xanh lam

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

float scale_factor_v2 = 20.0f;

void canhQUATTRAI_V2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(4.0f / scale_factor_v2, 0.15f / scale_factor_v2, 0.7f / scale_factor_v2)) * translate(vec3(0.6 / scale_factor_v2, 32.5 / scale_factor_v2, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0f, 0.4f, 1.0f, 1.0f); // Màu xanh dương đồng nhất
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATPHAI_V2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(4.0f / scale_factor_v2, 0.15f / scale_factor_v2, 0.7f / scale_factor_v2)) * translate(vec3(-0.6 / scale_factor_v2, 32.5 / scale_factor_v2, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0f, 0.4f, 1.0f, 1.0f); // Màu xanh dương đồng nhất

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRUOC_V2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.7f / scale_factor_v2, 0.15f / scale_factor_v2, 4.0f / scale_factor_v2)) * translate(vec3(0.0, 32.5 / scale_factor_v2, 0.0)) * rotate_y(90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0f, 0.4f, 1.0f, 1.0f); // Màu xanh dương đồng nhất

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATSAU_V2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.7f / scale_factor_v2, 0.15f / scale_factor_v2, 4.0f / scale_factor_v2)) * translate(vec3(0.0, 32.5 / scale_factor_v2, 0.0)) * rotate_y(-90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0f, 0.4f, 1.0f, 1.0f); // Màu xanh dương đồng nhất

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void XEBUS(float x, float z)
{
	mvstack.push(model_mat_cpp);

	// Thân xe (hình hộp) - điều chỉnh chiều cao thân xe
	float bus_length = 0.35f;   // Chiều dài xe
	float bus_width = 0.12f;    // Chiều rộng xe
	float bus_height = 0.1f;   // Chiều cao xe (tăng lên)
	model_mat_cpp = model_mat_cpp * translate(vec3(x,0.02 +  bus_height / 2 + 0.02, z)) * rotate_y(-90.0f); // Đặt vị trí cho thân xe
	mat4 instance = scale(vec3(bus_length, bus_height, bus_width)); // Tạo hình hộp cho thân xe
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.7f, 0.7f, 0.2f, 1.0f); // Màu vàng cho thân xe
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Bánh xe (hình trụ)
	float wheel_radius = 0.02f; // Bán kính bánh xe
	float wheel_width = 0.03f;  // Bề rộng bánh xe

	// Tọa độ tương đối của các bánh xe so với thân xe
	vec3 wheel_positions[6] = {
		vec3(bus_length / 4, -bus_height / 2, bus_width / 2),   // Bánh trước bên phải
		vec3(bus_length / 4, -bus_height / 2, -bus_width / 2),  // Bánh trước bên trái
		vec3(-bus_length / 4, -bus_height / 2, bus_width / 2),  // Bánh sau bên phải
		vec3(-bus_length / 4, -bus_height / 2, -bus_width / 2), // Bánh sau bên trái
		vec3(bus_length / 2, -bus_height / 2, bus_width / 2),   // Bánh giữa bên phải
		vec3(bus_length / 2, -bus_height / 2, -bus_width / 2)   // Bánh giữa bên trái
	};

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 360; j += 20) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(wheel_positions[i]) * translate(vec3(-0.03f, -0.01f, 0.0f)) * rotate_z(j); // Đặt vị trí bánh xe
			instance = scale(vec3(wheel_radius, wheel_width, wheel_radius)); // Tạo kích thước bánh xe lớn hơn
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
			glUniform4f(colorLocation, 0.1f, 0.1f, 0.1f, 1.0f); // Màu đen cho bánh xe
			glDrawArrays(GL_TRIANGLES, 0, 36);
			model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó
		}
	}

	// Thêm phần mui xe (nhô lên giữa xe)
	mvstack.push(model_mat_cpp);
	float roof_height = 0.03f;  // Chiều cao mui xe
	float roof_length = 0.2f;   // Chiều dài mui xe
	float roof_width = 0.1f;    // Chiều rộng mui xe
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, bus_height / 2 + roof_height / 2, 0.0f)); // Vị trí mui xe
	instance = scale(vec3(roof_length, roof_height, roof_width)); // Kích thước mui xe
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.9f, 0.9f, 0.9f, 1.0f); // Màu bạc cho mui xe
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Thêm cửa kính phía trước (Trước kính chắn gió)
	float front_window_height = 0.03f;  // Chiều cao cửa kính phía trước
	float front_window_length = 0.12f;  // Chiều dài cửa kính phía trước
	float front_window_width = 0.02f;   // Chiều rộng cửa kính phía trước

	// Vị trí cửa kính phía trước
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.17f,-0.05 + bus_height / 2 + front_window_height / 2, -0.05f + bus_width / 2)) * rotate_y(90); // Vị trí cửa kính phía trước
	instance = scale(vec3(front_window_length, front_window_height, front_window_width)); // Kích thước cửa kính
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.2f, 0.5f, 0.8f, 1.0f); // Màu cửa kính (xanh dương)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Thêm kính chắn gió (nhô lên)
	mvstack.push(model_mat_cpp);
	float windshield_height = 0.02f;  // Chiều cao kính chắn gió
	float windshield_length = 0.12f;  // Chiều dài kính chắn gió
	float windshield_width = 0.08f;   // Chiều rộng kính chắn gió
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.05f, bus_height / 2 + windshield_height / 2, -0.0f)); // Vị trí kính chắn gió
	instance = scale(vec3(windshield_length, windshield_height, windshield_width)); // Kích thước kính chắn gió
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.6f, 0.8f, 0.6f, 1.0f); // Màu kính (xanh lá nhạt)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Thêm cửa kính
	float window_height = 0.05f; // Chiều cao cửa kính
	float window_length = 0.12f; // Chiều dài cửa kính
	float window_width = 0.02f;  // Chiều rộng cửa kính (mỏng hơn)

	// Vị trí cửa kính bên trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-bus_length / 7, cuakinhxebus/2 + bus_height / 5, bus_width / 2)); // Vị trí cửa kính bên trái
	instance = scale(vec3(window_length, cuakinhxebus + window_height, window_width)); // Kích thước cửa kính
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.2f, 0.5f, 0.8f, 1.0f); // Màu kính cửa (xanh dương)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Vị trí cửa kính bên phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-bus_length / 7, bus_height / 5, -bus_width / 2)); // Vị trí cửa kính bên phải
	instance = scale(vec3(window_length, window_height, window_width)); // Kích thước cửa kính
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.2f, 0.5f, 0.8f, 1.0f); // Màu kính cửa (xanh dương)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Vị trí cửa kính bên trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.15 -bus_length / 7, cuakinhxebus / 2 + bus_height / 5, bus_width / 2)); // Vị trí cửa kính bên trái
	instance = scale(vec3(window_length, cuakinhxebus + window_height, window_width)); // Kích thước cửa kính
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.2f, 0.5f, 0.8f, 1.0f); // Màu kính cửa (xanh dương)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Vị trí cửa kính bên phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.15-bus_length / 7, bus_height / 5, -bus_width / 2)); // Vị trí cửa kính bên phải
	instance = scale(vec3(window_length, window_height, window_width)); // Kích thước cửa kính
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.2f, 0.5f, 0.8f, 1.0f); // Màu kính cửa (xanh dương)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó


	// Thêm cần gạt mưa (Windshield Wiper)
	mvstack.push(model_mat_cpp);
	float wiper_length = 0.06f;  // Chiều dài cần gạt mưa
	float wiper_width = 0.005f; // Chiều rộng cần gạt mưa
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.18f, -0.05 + bus_height / 2 + front_window_height / 2, -0.06f + bus_width / 2)) 
		* translate(vec3(0.0f, -0.03f, 0.0f)) * rotate_x(alcanGat) * translate(vec3(0.0f, 0.03f, 0.0f)); // Vị trí cần gạt mưa
	instance = scale(vec3(wiper_width, wiper_length, wiper_width)); // Kích thước cần gạt mưa
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.1f, 0.1f, 0.1f, 1.0f); // Màu đen cho cần gạt mưa
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Thêm cần gạt mưa (Windshield Wiper)
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.18f, -0.05 + bus_height / 2 + front_window_height / 2, -0.03f + bus_width / 2))
		* translate(vec3(0.0f, -0.03f, 0.0f)) * rotate_x(alcanGat) * translate(vec3(0.0f, 0.03f, 0.0f)); // Vị trí cần gạt mưa
	instance = scale(vec3(wiper_width, wiper_length, wiper_width)); // Kích thước cần gạt mưa
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp* instance).m);
	glUniform4f(colorLocation, 0.1f, 0.1f, 0.1f, 1.0f); // Màu đen cho cần gạt mưa
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Thêm gương chiếu hậu (Side Mirrors)
	// Gương bên trái
	mvstack.push(model_mat_cpp);
	float mirror_radius = 0.01f; // Bán kính gương
	model_mat_cpp = model_mat_cpp * translate(vec3(-bus_length / 2, bus_height / 2 + 0.02f, bus_width / 2)); // Vị trí gương bên trái
	instance = scale(vec3(mirror_radius, mirror_radius, mirror_radius)); // Kích thước gương
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.8f, 1.0f); // Màu gương (xám)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	// Gương bên phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-bus_length / 2, bus_height / 2 + 0.02f, -bus_width / 2)); // Vị trí gương bên phải
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop(); // Phục hồi trạng thái trước đó

	model_mat_cpp = mvstack.pop();
}

float scaleFactor = 30.0f; // Chia cho scaleFactor



void tuongSAUM1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(5.0f / scaleFactor, 0.0f / scaleFactor, 0.5f / scaleFactor)) * scale(vec3(14.0f / scaleFactor, 10.0f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Thiết lập màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.7f, 0.7f, 0.7f, 1.0f); // Màu xám cho tường

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongSAUM2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-6.5f / scaleFactor, 4.75f / scaleFactor, 0.5f / scaleFactor)) * scale(vec3(9.0f / scaleFactor, 0.5f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Thiết lập màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám đậm cho phần tường

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongSAUM3()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-6.5f / scaleFactor, -4.35f / scaleFactor, 0.5f / scaleFactor)) * scale(vec3(9.0f / scaleFactor, 1.3f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Thiết lập màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6f, 0.6f, 0.6f, 1.0f); // Màu xám nhạt cho phần tường

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongSAUM4()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.5f / scaleFactor, 0.0f / scaleFactor, 0.5f / scaleFactor)) * scale(vec3(1.0f / scaleFactor, 10.0f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Thiết lập màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.8f, 1.0f); // Màu sáng cho tường

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void khungSOTRAI()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(4.25f / scaleFactor, 0.4f / scaleFactor, 0.5f / scaleFactor)) *
		scale(vec3(0.5f / scaleFactor, 8.2f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám cho khung trái

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void khungSOPHAI()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(-4.25f / scaleFactor, 0.4f / scaleFactor, 0.5f / scaleFactor)) *
		scale(vec3(0.5f / scaleFactor, 8.2f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám cho khung phải

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void khungSOTREN1()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 4.45f / scaleFactor, 0.5f / scaleFactor)) *
		scale(vec3(8.0f / scaleFactor, 0.1f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám cho khung trên 1

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void khungSOTREN2()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.5f / scaleFactor, 0.5f / scaleFactor)) *
		scale(vec3(8.0f / scaleFactor, 0.1f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám cho khung trên 2

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void khungSOTRENCHIA()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.95f / scaleFactor, 0.5f / scaleFactor)) *
		scale(vec3(0.5f / scaleFactor, 0.9f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám cho khung trên chía

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void khungSODUOI()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.6f / scaleFactor, 0.5f / scaleFactor)) *
		scale(vec3(8.0f / scaleFactor, 0.2f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám cho khung dưới

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void matKINHTRAI()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(2.125f / scaleFactor, 3.95f / scaleFactor, -0.15f / scaleFactor)) *
		scale(vec3(3.75f / scaleFactor, 0.9f / scaleFactor, 0.2f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.8f, 1.0f); // Màu sáng cho kính trái

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void matKINHPHAI()
{
	mvstack.push(model_mat_cpp);

	// Chia tất cả các giá trị translate và scale cho scaleFactor
	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.125f / scaleFactor, 3.95f / scaleFactor, -0.15f / scaleFactor)) *
		scale(vec3(3.75f / scaleFactor, 0.9f / scaleFactor, 0.2f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.8f, 1.0f); // Màu sáng cho kính phải

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soTRAIGIUA01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(2.0f / scaleFactor, 1.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Khai báo và gửi màu sắc cục bộ
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6f, 0.6f, 0.6f, 1.0f);  // Màu xám nhạt

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chansongCOT1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 0.0f, 0.6f / scaleFactor)) * scale(vec3(0.25f / scaleFactor, 7.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Khai báo và gửi màu sắc cục bộ
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void chansongCOT2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0f / scaleFactor, 0.0f, 0.6f / scaleFactor)) * scale(vec3(0.25f / scaleFactor, 7.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Khai báo và gửi màu sắc cục bộ
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.3f, 0.6f, 0.3f, 1.0f);  // Màu xanh lá

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void chansongCOT3()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.0f / scaleFactor, 0.0f, 0.6f / scaleFactor)) * scale(vec3(0.25f / scaleFactor, 7.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Khai báo và gửi màu sắc cục bộ
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.2f, 0.2f, 1.0f);  // Màu đỏ

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void chansongNGANG1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 1.0f / scaleFactor, 0.6f / scaleFactor)) * scale(vec3(8.0f / scaleFactor, 0.25f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Khai báo và gửi màu sắc cục bộ
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.3f, 0.3f, 0.8f, 1.0f);  // Màu xanh dương nhạt

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void chansongNGANG2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -1.0f / scaleFactor, 0.6f / scaleFactor)) * scale(vec3(8.0f / scaleFactor, 0.25f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Khai báo và gửi màu sắc cục bộ
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.7f, 0.7f, 0.3f, 1.0f);  // Màu vàng nhạt

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soPHAIGIUA02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(2.0f / scaleFactor, 1.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAITRENO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -0.625f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 0.25f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.8f, 0.2f, 1.0f);  // Màu xanh lá

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soPHAIO01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -1.5f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 1.5f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.2f, 0.2f, 1.0f);  // Màu đỏ

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAITRAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f / scaleFactor, -1.5f / scaleFactor, 0.0f)) * scale(vec3(0.25f / scaleFactor, 2.0f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.2f, 1.0f);  // Màu vàng

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAIPHAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f / scaleFactor, -1.5f / scaleFactor, 0.0f)) * scale(vec3(0.25f / scaleFactor, 2.0f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.2f, 1.0f);  // Màu vàng

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAIDUOIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -2.375f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 0.25f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6f, 0.2f, 0.6f, 1.0f);  // Màu tím

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soPHAIDUOI02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.0f / scaleFactor, 0.0f)) * scale(vec3(2.0f / scaleFactor, 1.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.4f, 0.6f, 0.2f, 1.0f);  // Màu xanh lá nhạt

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAIDUOIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 0.625f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 0.25f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.4f, 0.8f, 0.6f, 1.0f);  // Màu xanh lá nhạt

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soPHAIO02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 1.5f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 1.5f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.2f, 0.2f, 1.0f);  // Màu đỏ

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAITRAIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f / scaleFactor, 1.5f / scaleFactor, 0.0f)) * scale(vec3(0.25f / scaleFactor, 2.0f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.2f, 1.0f);  // Màu vàng

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAIPHAIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f / scaleFactor, 1.5f / scaleFactor, 0.0f)) * scale(vec3(0.25f / scaleFactor, 2.0f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.8f, 0.2f, 1.0f);  // Màu vàng

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongPHAITRENO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 2.375f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 0.25f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6f, 0.4f, 0.2f, 1.0f);  // Màu nâu

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soPHAITREN02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.0f / scaleFactor, 0.0f)) * scale(vec3(2.0f / scaleFactor, 1.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.6f, 0.2f, 1.0f);  // Màu vàng nhạt

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soPHAITRAI02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.5f / scaleFactor, 0.0f, 0.0f)) * scale(vec3(1.0f / scaleFactor, 7.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.6f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soPHAIPHAI02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.5f / scaleFactor, 0.0f, 0.0f)) * scale(vec3(1.0f / scaleFactor, 7.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Màu sắc
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.6f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}





void road1()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.30, 0.021, 1.4));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void road2()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(1.4, 0.021, 0.30));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}


// ----------------------------------------------------------------------------

void tuongPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-12.75f / scaleFactor, 1.99f / scaleFactor, 0.0f))
		* rotate_z(90)
		* scale(vec3(10.0f / scaleFactor, 1.5f / scaleFactor, 23.0f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(12.75f / scaleFactor, 1.99f / scaleFactor, 0.0f))
		* rotate_z(-90)
		* scale(vec3(10.0f / scaleFactor, 1.5f / scaleFactor, 23.0f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongTRUOCPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(8.495f / scaleFactor, 1.99f / scaleFactor, 10.75f / scaleFactor))
		* scale(vec3(7.0f / scaleFactor, 10.0f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongTRUOCTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-8.495f / scaleFactor, 1.99f / scaleFactor, 10.75f / scaleFactor))
		* scale(vec3(7.0f / scaleFactor, 10.0f / scaleFactor, 1.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng màu sắc thay vì texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu xanh dương

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAITRENO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -0.625f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 0.25f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Thay đổi màu sắc hợp lý
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soTRAIO01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -1.5f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 1.5f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Thay đổi màu sắc hợp lý
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAITRAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f / scaleFactor, -1.5f / scaleFactor, 0.0f)) * scale(vec3(0.25f / scaleFactor, 2.0f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Thay đổi màu sắc hợp lý
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAIPHAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f / scaleFactor, -1.5f / scaleFactor, 0.0f)) * scale(vec3(0.25f / scaleFactor, 2.0f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Thay đổi màu sắc hợp lý
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAIDUOIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -2.375f / scaleFactor, 0.0f)) * scale(vec3(1.5f / scaleFactor, 0.25f / scaleFactor, 0.25f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Thay đổi màu sắc hợp lý
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soTRAIDUOI01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.0f / scaleFactor, 0.0f)) * scale(vec3(2.0f / scaleFactor, 1.0f / scaleFactor, 0.5f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Thay đổi màu sắc hợp lý
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAIDUOIO2() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 0.625f, 0.0f) / scaleFactor) * scale(vec3(1.5f, 0.25f, 0.25f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soTRAIO02() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 1.5f, 0.0f) / scaleFactor) * scale(vec3(1.5f, 1.5f, 0.5f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAITRAIO2() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f, 1.5f, 0.0f) / scaleFactor) * scale(vec3(0.25f, 2.0f, 0.25f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAIPHAIO2() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f, 1.5f, 0.0f) / scaleFactor) * scale(vec3(0.25f, 2.0f, 0.25f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void mongTRAITRENO2() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 2.375f, 0.0f) / scaleFactor) * scale(vec3(1.5f, 0.25f, 0.25f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soTRAITREN01() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.0f, 0.0f) / scaleFactor) * scale(vec3(2.0f, 1.0f, 0.5f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soTRAITRAI01() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(1.5f, 0.0f, 0.0f) / scaleFactor) * scale(vec3(1.0f, 7.0f, 0.5f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void soTRAIPHAI01() {
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.5f, 0.0f, 0.0f) / scaleFactor) * scale(vec3(1.0f, 7.0f, 0.5f) / scaleFactor);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.2f, 0.8f, 1.0f);  // Màu sắc phù hợp
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}



void tuongTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	// Chia tất cả giá trị scale và translate cho scaleFactor
	instance = translate(vec3(0.0f, 7.75f / scaleFactor, 0.0f)) * scale(vec3(8.0f / scaleFactor, 1.0f / scaleFactor, 23.0f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng glUniform4f để thay đổi màu sắc đối tượng thay vì bind texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám cho khung trên 2

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void GHEBENXE()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	// Chia tất cả giá trị scale và translate cho scaleFactor
	instance = translate(vec3(0.0f, 7.75f / scaleFactor, 0.0f)) * scale(vec3(2.0f / scaleFactor, 1.0f / scaleFactor, 18.0f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng glUniform4f để thay đổi màu sắc đối tượng thay vì bind texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.7f, 0.9f, 0.9f, 1.0f); // Màu xám cho khung trên 2

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void GHEBENXETUALUNG()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	// Chia tất cả giá trị scale và translate cho scaleFactor
	instance = translate(vec3(0.75f / scaleFactor, 8.75f / scaleFactor, 0.0f)) * scale(vec3(0.5f / scaleFactor, 3.0f / scaleFactor, 18.0f / scaleFactor));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);

	// Sử dụng glUniform4f để thay đổi màu sắc đối tượng thay vì bind texture
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.9f, 0.9f, 0.9f, 0.1f); // Màu xám cho khung trên 2

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void CAMERA(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");

	// Bánh xe (hình trụ)
	float wheel_radius = 0.05f; // Bán kính bánh xe (tăng 50%)
	float wheel_width = 0.025f; // Bề rộng bánh xe (tăng 50%)
	model_mat_cpp = model_mat_cpp * translate(vec3(x, 0.0f, z)) * rotate_y(y); // Dịch chuyển theo x, y và z

	// Sử dụng vòng lặp để tạo bánh xe
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 360; j += 20) {
			mvstack.push(model_mat_cpp);

			// Đặt vị trí bánh xe với các tham chiếu x, y, z
			model_mat_cpp = model_mat_cpp * rotate_z(j); // Đặt vị trí bánh xe theo góc quay

			// Tạo kích thước bánh xe lớn hơn
			instance = scale(vec3(wheel_radius, wheel_width, wheel_radius));

			// Cập nhật ma trận và vẽ bánh xe
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
			glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, 1.0f); // Màu trắng cho bánh xe
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Phục hồi trạng thái trước đó
			model_mat_cpp = mvstack.pop();

			mvstack.push(model_mat_cpp);

			// Đặt vị trí bánh xe với các tham chiếu x, y, z
			model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 0.0f, wheel_width)) * rotate_z(j); // Đặt vị trí bánh xe theo góc quay

			// Tạo kích thước bánh xe lớn hơn
			instance = scale(vec3(wheel_radius/2, wheel_width, wheel_radius/2));

			// Cập nhật ma trận và vẽ bánh xe
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_mat_cpp * instance).m);
			glUniform4f(colorLocation, 0.1f, 0.01f, 0.2f, 1.0f); // Màu đen cho bánh xe
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Phục hồi trạng thái trước đó
			model_mat_cpp = mvstack.pop();
		}
	}
}



////khai báo toàn cục
vec3 eye(0.1f, -0.1f, 0.1f);
vec3 at(0.0f, 0.0f, 0.0f);
vec3 up(0.0f, 1.0f, 0.0f);




void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (rotated)
	{
		model_mat_cpp = model_mat_cpp * rotate_x(r[0])
			* rotate_y(r[1])
			* rotate_z(r[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (scaled)
	{
		model_mat_cpp = model_mat_cpp * scale(vec3(s[0], s[1], s[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,       // Cắt gần
		zfar = 1000.0f,     // Cắt xa (có thể điều chỉnh tùy thuộc vào phạm vi cảnh vật)
		fov = 45.0f,        // Góc nhìn
		aspect = (float)CurrentWidth / CurrentHeight;  // Tỷ lệ khung hình
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);
	GLint light1Loc = glGetUniformLocation(ProgramId, "light1_enabled");
	glUniform1i(light1Loc, light1Enabled);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.9, 0.9, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	// vẽ
	MATDAT();
	KERDUONGDI();
	CONDUONG();
	VIAHE();
	VEDUONGDI();
	THUNGRAC(-0.25f, 0.45f);
	XEOTO(-0.4f, otodichuyen);
	XEOTO_DO(-0.6f, otodichuyen2);
	XEOTO_DO(0.3f, -0.2f);
	XEOTO(0.1f, -0.2f);
	//chong chong
	mvstack.push(model_mat_cpp);	
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.2f, 0.05f, -0.4f));
	duiQUAT();
	trucQUAT();
	model_mat_cpp = model_mat_cpp * rotate_y(alphaQuat);
	tamQUAT();
	canhQUATTRAI();
	canhQUATPHAI();
	canhQUATTRUOC();
	canhQUATSAU();
	model_mat_cpp = mvstack.pop();
//tram
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.75f, 0.12f + 1.99f / scaleFactor,0.47f + -11.25f / scaleFactor)) * rotate_y(-90);
	tuongSAUM1();
	tuongSAUM2();
	tuongSAUM3();
	tuongSAUM4();
	//khungcuaso
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-6.5f / scaleFactor, 0.0f, 0.0f));
	khungSOTRAI();
	khungSOPHAI();
	khungSOTREN1();
	khungSOTREN2();
	khungSOTRENCHIA();
	matKINHTRAI();
	matKINHPHAI();
	khungSODUOI();
	//chấn song
	chansongCOT1();
	chansongCOT2();
	chansongCOT3();
	chansongNGANG1();
	chansongNGANG2();
	//cánh trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(4.0f / scaleFactor, 0.0f, -0.25f / scaleFactor))
		* rotate_y(-alcuaSo)
		* translate(vec3(-2.0f / scaleFactor, 0.0f, 0.25f / scaleFactor));
	soTRAIGIUA01();
	mongTRAITRENO1();
	soTRAIO01();
	mongTRAITRAIO1();
	mongTRAIPHAIO1();
	mongTRAIDUOIO1();
	soTRAIDUOI01();
	mongTRAIDUOIO2();
	soTRAIO02();
	mongTRAITRAIO2();
	mongTRAIPHAIO2();
	mongTRAITRENO2();
	soTRAITREN01();
	soTRAITRAI01();
	soTRAIPHAI01();
	model_mat_cpp = mvstack.pop();
	// cánh phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-4.0f / scaleFactor, 0.0f, -0.25f / scaleFactor))
		* rotate_y(alcuaSo)
		* translate(vec3(2.0f / scaleFactor, 0.0f, 0.25f / scaleFactor));
	soPHAIGIUA02();
	mongPHAITRENO1();
	soPHAIO01();
	mongPHAITRAIO1();
	mongPHAIPHAIO1();
	mongPHAIDUOIO1();
	soPHAIDUOI02();
	mongPHAIDUOIO2();
	soPHAIO02();
	mongPHAITRAIO2();
	mongPHAIPHAIO2();
	mongPHAITRENO2();
	soPHAITREN02();
	soPHAITRAI02();
	soPHAIPHAI02();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
	// tường trên
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.65f, 0.1f, 0.095f));
	tuongTREN();
	model_mat_cpp = mvstack.pop();

	// tường trên
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.65f, -0.2f, 0.08f));
	GHEBENXE();
	GHEBENXETUALUNG();
	model_mat_cpp = mvstack.pop();

	XEBUS(0.1f, 0.15f + xebusdichuyen);
	XEBUS(0.3f, 0.15f);

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.55f, 0.2863f, 0.095f));
	duiQUAT();
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 0.043f, 0.0f));
	trucQUAT();
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, -0.043f, 0.0f));
	model_mat_cpp = model_mat_cpp * rotate_y(alphaQuat);
	tamQUAT();
	canhQUATTRAI_V2();
	canhQUATPHAI_V2();
	canhQUATTRUOC_V2();
	canhQUATSAU_V2();
	model_mat_cpp = mvstack.pop();
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.38f, 0.4763f, 0.095f)) * rotate_y(-90);
	CAMERA(0.0f, alcamera, 0.0f);
	model_mat_cpp = mvstack.pop();


	glutSwapBuffers();
}
// ---------------------------------------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	glutPostRedisplay();
}

void IdleFunc1(void)
{
	// tính toán góc quay
	alphaQuat += 1.0f;
	if (alphaQuat > 360.0f) {
		alphaQuat -= 360.0f;
		light1Enabled = !light1Enabled;
	}

	if (otoxoay) {
		otodichuyen += 0.001;
		if (otodichuyen > 0.4)
			otoxoay = !otoxoay;
	}
	else
	{
		otodichuyen -= 0.001;
		if (otodichuyen < -0.4)
			otoxoay = !otoxoay;
	}
	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}
void IdleFunc2(void)
{
	// tính toán góc quay
	alphaQuat += 2.0f;
	if (alphaQuat > 360.0f) {
		alphaQuat -= 360.0f;
		light1Enabled = !light1Enabled;
	}

	if (otoxoay) {
		otodichuyen += 0.001;
		if (otodichuyen > 0.4)
			otoxoay = !otoxoay;
	}
	else
	{
		otodichuyen -= 0.001;
		if (otodichuyen < -0.4)
			otoxoay = !otoxoay;
	}

	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}
void IdleFunc3(void)
{
	// tính toán góc quay
	alphaQuat += 4.0f;
	if (alphaQuat > 360.0f) {
		alphaQuat -= 360.0f;
		light1Enabled = !light1Enabled;
	}

	if (otoxoay) {
		otodichuyen += 0.001;
		if (otodichuyen > 0.4)
			otoxoay = !otoxoay;
	}
	else
	{
		otodichuyen -= 0.001;
		if (otodichuyen < -0.4)
			otoxoay = !otoxoay;
	}

	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}

// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'x':
		r[0] -= 10.0f;
		rotated = true;
		break;
	case 'X':
		r[0] += 10.0f;
		rotated = true;
		break;

	case 'y':
		r[1] -= 10.0f;
		rotated = true;
		break;
	case 'Y':
		r[1] += 10.0f;
		rotated = true;
		break;

	case 'z':
		r[2] -= 10.0f;
		rotated = true;
		break;
	case 'Z':
		r[2] += 10.0f;
		rotated = true;
		break;

	case '=':
	case '+':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '-':
	case '_':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;

	case 'j':
		t[0] -= 0.05f;
		translated = true;
		break;
	case 'l':
		t[0] += 0.05f;
		translated = true;
		break;
	case 'i':
		t[1] += 0.05f;
		translated = true;
		break;
	case ',':
		t[1] -= 0.05f;
		translated = true;
		break;
	case 'g':
		t[2] -= 0.05f;
		translated = true;
		break;
	case 'h':
		t[2] += 0.05f;
		translated = true;
		break;

	case 'b':
		alcanGat += 10;
		if (alcanGat > 45) alcanGat = 45;  // Giới hạn trên
		break;
	case 'B':
		alcanGat -= 10;
		if (alcanGat < -45) alcanGat = -45;   // Giới hạn dưới
		break;

	case 'n':
		alcuaSo += 10;
		if (alcuaSo > 90) alcuaSo = 90;  // Giới hạn trên
		break;
	case 'N':
		alcuaSo -= 10;
		if (alcuaSo < -90) alcuaSo = -90;   // Giới hạn dưới
		break;

	case 'm':
		alcamera += 3;
		if (alcamera > 60) alcamera = 60;  // Giới hạn trên
		break;
	case 'M':
		alcamera -= 3;
		if (alcamera < -60) alcamera = -60;   // Giới hạn dưới
		break;

	case 'v':
		otodichuyen2 += 0.01;
		if (otodichuyen2 > 0.5) otodichuyen2 = 0.5;  // Giới hạn trên
		break;
	case 'V':
		otodichuyen2 -= 0.01;
		if (otodichuyen2 < -0.5) otodichuyen2 = -0.5;   // Giới hạn dưới
		break;
	case 'f':
		xebusdichuyen += 0.002;
		if (xebusdichuyen > 0.2) xebusdichuyen = 0.2;  // Giới hạn trên
		break;
	case 'F':
		xebusdichuyen -= 0.002;
		if (xebusdichuyen < -0.1) xebusdichuyen = -0.1;   // Giới hạn dưới
		break;
	case 'c':
		cuakinhxebus += 0.001;
		if (cuakinhxebus > 0.0f) cuakinhxebus = 0.0f;  // Giới hạn trên
		break;
	case 'C':
		cuakinhxebus -= 0.001;
		if (cuakinhxebus < -0.05) cuakinhxebus = -0.05;   // Giới hạn dưới
		break;


	case '1': // Bật tắt đèn
		light1Enabled = !light1Enabled;
		glutPostRedisplay();
		break;
	case '2':///quạt số 1
		glutIdleFunc(IdleFunc1);
		break;
	case '3':///quạt số 2
		glutIdleFunc(IdleFunc2);
		break;
	case '4':// quạt số 3
		glutIdleFunc(IdleFunc3);
		break;
	case '5'://tắt quạt
		glutIdleFunc(IdleFunc);
		break;
	}

}

// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Cube");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	//glutIdleFunc(IdleFunc);
	glutIdleFunc(IdleFunc3);
	glutKeyboardFunc(KeyboardFunc);
	glutCloseFunc(CloseFunc);
	glutMainLoop();

	return 0;
}
// -------------------------------------