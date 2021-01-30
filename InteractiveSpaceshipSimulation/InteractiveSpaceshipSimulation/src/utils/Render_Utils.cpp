#include "../../headers/utils/Render_Utils.h"


void Core::RenderContext::initFromOBJ(obj::Model& model)
{
    vertexArray = 0;
    vertexBuffer = 0;	
    vertexIndexBuffer = 0;
	
	instanceModelMatrixesBuffer = 0;
    unsigned int vertexDataBufferSize = sizeof(float) * model.vertex.size();
    unsigned int vertexNormalBufferSize = sizeof(float) * model.normal.size();
    unsigned int vertexTexBufferSize = sizeof(float) * model.texCoord.size();
	unsigned int vertexTangentBufferSize = sizeof(float) * model.tangent.size();
	unsigned int vertexBitangentBufferSize = sizeof(float) * model.bitangent.size();


    size = model.faces["default"].size();
    unsigned int vertexElementBufferSize = sizeof(unsigned short) * size;


    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);


    glGenBuffers(1, &vertexIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexElementBufferSize, &model.faces["default"][0], GL_STATIC_DRAW);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

	glEnableVertexAttribArray(7);
	glEnableVertexAttribArray(8);

    glBufferData(GL_ARRAY_BUFFER, vertexDataBufferSize + vertexNormalBufferSize + vertexTexBufferSize + vertexTangentBufferSize + vertexBitangentBufferSize, 
		NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataBufferSize, &model.vertex[0]);

    glBufferSubData(GL_ARRAY_BUFFER, vertexDataBufferSize, vertexNormalBufferSize, &model.normal[0]);

    glBufferSubData(GL_ARRAY_BUFFER, vertexDataBufferSize + vertexNormalBufferSize, vertexTexBufferSize, &model.texCoord[0]);

	glBufferSubData(GL_ARRAY_BUFFER, vertexDataBufferSize + vertexNormalBufferSize + vertexTexBufferSize, vertexTangentBufferSize, &model.tangent[0]);

	glBufferSubData(GL_ARRAY_BUFFER, vertexDataBufferSize + vertexNormalBufferSize + vertexTexBufferSize + vertexTangentBufferSize,
		vertexBitangentBufferSize, &model.bitangent[0]);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(vertexDataBufferSize));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(vertexNormalBufferSize + vertexDataBufferSize));

	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 0, (void*)(vertexDataBufferSize + vertexNormalBufferSize + vertexTexBufferSize));
	glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 0, (void*)(vertexDataBufferSize + vertexNormalBufferSize + vertexTexBufferSize + vertexTangentBufferSize));


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Core::RenderContext::initInstanceBuffer()
{
	if (instanceModelMatrixesBuffer == 0)
	{
		glBindVertexArray(vertexArray);
		glGenBuffers(1, &instanceModelMatrixesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, instanceModelMatrixesBuffer);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
}

void Core::RenderContext::sendInstanceBufferData(unsigned int instanceNum, std::vector<glm::mat4> &modelMatrixes)
{
	if (instanceModelMatrixesBuffer != 0)
	{
		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, instanceModelMatrixesBuffer);
		glBufferData(GL_ARRAY_BUFFER, instanceNum * sizeof(glm::mat4), &modelMatrixes[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
}

void Core::DrawContext(Core::RenderContext& context)
{

	glBindVertexArray(context.vertexArray);
	glDrawElements(
		GL_TRIANGLES,      // mode
		context.size,    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
	);
	glBindVertexArray(0);
}

void Core::DrawContextInstanced(RenderContext& context, unsigned int instanceNum, std::vector<glm::mat4> &modelMatrixes)
{
	if (context.instanceModelMatrixesBuffer != 0)
	{
		context.sendInstanceBufferData(instanceNum, modelMatrixes);
		glBindVertexArray(context.vertexArray);
		glDrawElementsInstanced(
			GL_TRIANGLES,
			context.size,
			GL_UNSIGNED_SHORT,
			(void*)0,
			instanceNum
		);
		glBindVertexArray(0);
	}
}


void Core::DrawVertexArray(const float * vertexArray, int numVertices, int elementSize )
{
	glVertexAttribPointer(0, elementSize, GL_FLOAT, false, 0, vertexArray);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void Core::DrawVertexArrayIndexed( const float * vertexArray, const int * indexArray, int numIndexes, int elementSize )
{
	glVertexAttribPointer(0, elementSize, GL_FLOAT, false, 0, vertexArray);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, numIndexes, GL_UNSIGNED_INT, indexArray);
}


void Core::DrawVertexArray( const VertexData & data )
{
	int numAttribs = std::min(VertexData::MAX_ATTRIBS, data.NumActiveAttribs);
	for(int i = 0; i < numAttribs; i++)
	{
		glVertexAttribPointer(i, data.Attribs[i].Size, GL_FLOAT, false, 0, data.Attribs[i].Pointer);
		glEnableVertexAttribArray(i);
	}
	glDrawArrays(GL_TRIANGLES, 0, data.NumVertices);
}

void Core::DrawModel( obj::Model * model )
{
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &model->vertex[0]);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, &model->texCoord[0]);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, &model->normal[0]);
	//glVertexAttribPointer(4, 3, GL_FLOAT, false, 0, &model->tangent[0]);
	//glVertexAttribPointer(5, 3, GL_FLOAT, false, 0, &model->bitangent[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(4);
	//glEnableVertexAttribArray(5);

	unsigned short * tmp = &model->faces["default"][0];
	glDrawElements(GL_TRIANGLES, model->faces["default"].size(), GL_UNSIGNED_SHORT, tmp);
}
