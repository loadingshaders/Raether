#include "Mesh.h"

#ifdef _MSC_VER
#pragma warning (push, 0)
#endif

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#define TINYGLTF_NO_INCLUDE_JSON     // If you've included json.hpp elsewhere
#define TINYGLTF_NO_INCLUDE_STB_IMAGE  // If you've included stb_image.h elsewhere
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tinygltf/tiny_gltf.h"

Mesh::Mesh(const char* modelFilename, double scale, std::shared_ptr<Material> matid) :
	Scale(scale),
	MaterialId(matid),
	RootNode(nullptr)
{
	std::string Filename(modelFilename);
	std::string err, warn;

	if (LoadModel("assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../../../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../../../../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../../../../../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../../../../../../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../../../../../../../assets/mesh/" + Filename, err, warn)) return;
	if (LoadModel("../../../../../../../../../assets/mesh/" + Filename, err, warn)) return;

	if (!warn.empty()) std::cout << "Warning: " << warn << std::endl;

	if (!err.empty()) std::cout << "Error: " << err << std::endl;

	std::cerr << "Failed to parse glTF file: '" << Filename << "'\n";
}

void Mesh::Add(std::shared_ptr<Hittable> object) {
	TriangleMesh.emplace_back(object);

	bbox = Aabb(bbox, object->BoundingBox());
}

void Mesh::BuildBVH() {
	if (RootNode == nullptr) {
		if (TriangleMesh.size() == 0) return;

		RootNode = RootNode->SplitBvh(TriangleMesh, 0, TriangleMesh.size());
	}
}

bool Mesh::LoadModel(std::string& modelFilename, std::string& err, std::string& warn) {
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	bool loadFile = loader.LoadBinaryFromFile(&model, &err, &warn, modelFilename);
	if (!loadFile) {
		return false;
	}

	/// Process all meshes in the model
	for (const auto& mesh : model.meshes) {
		for (const auto& primitive : mesh.primitives) {

			/// Get accessor for vertex positions
			const tinygltf::Accessor& posAccessor = model.accessors[primitive.attributes.find("POSITION")->second];
			const tinygltf::BufferView& posView = model.bufferViews[posAccessor.bufferView];
			const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];

			/// Get raw vertex data
			const float* positions = reinterpret_cast<const float*>(&posBuffer.data[posView.byteOffset + posAccessor.byteOffset]);

			/// Get accessor for indices if present
			std::vector<uint32_t> indices;
			if (primitive.indices >= 0) {
				
				const tinygltf::Accessor& indexAccessor = model.accessors[primitive.indices];
				const tinygltf::BufferView& indexView = model.bufferViews[indexAccessor.bufferView];
				const tinygltf::Buffer& indexBuffer = model.buffers[indexView.buffer];

				/// Get raw index data
				const uint16_t* rawIndices = reinterpret_cast<const uint16_t*>(
					&indexBuffer.data[indexView.byteOffset + indexAccessor.byteOffset]);

				/// Convert indices to uint32_t
				indices.resize(indexAccessor.count);
				for (size_t i = 0; i < indexAccessor.count; i++) {
					indices[i] = static_cast<uint32_t>(rawIndices[i]);
				}
			}

			// Create triangles
			for (size_t i = 0; i < indices.size(); i += 3) {

				glm::dvec3 v0(
					positions[indices[i] * 3],
					positions[indices[i] * 3 + 1],
					positions[indices[i] * 3 + 2]
				);
				glm::dvec3 v1(
					positions[indices[i + 1] * 3],
					positions[indices[i + 1] * 3 + 1],
					positions[indices[i + 1] * 3 + 2]
				);
				glm::dvec3 v2(
					positions[indices[i + 2] * 3],
					positions[indices[i + 2] * 3 + 1],
					positions[indices[i + 2] * 3 + 2]
				);

				Add(std::make_shared<Triangle>(v0 * Scale, v2 * Scale, v1 * Scale, MaterialId));
			}
		}
	}

	/// Build the entire triangle mesh bvh
	BuildBVH();

	return true;
}

bool Mesh::Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const {
	/// Check if the ray hits any triangles within the triangle mesh
	return RootNode->Hit(ray, hitdist, hitrecord);
}
