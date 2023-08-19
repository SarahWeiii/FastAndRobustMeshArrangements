import meshArrange as ma
import trimesh

# mesh = trimesh.load("/home/sarahwei/code/diffrec_ddmc/out/nerf_ship_tensorVM_preload_10k_t12_6_2_3x64_cuda_ddmc300_wd/mesh/mesh.ply")
mesh = trimesh.load("bunny.obj")
mesh.export("input.ply")

print(mesh.vertices.shape, mesh.faces.shape)
mesh = ma.Mesh(mesh.vertices, mesh.faces)
out = ma.intersectRemoval(mesh)
out = trimesh.Trimesh(out.vertices, out.indices)
print(out.vertices.shape, out.faces.shape)
out.export("output.ply")
