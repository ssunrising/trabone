Brief description:
    For 3D porous structures that are composed of two basic components - plates and rods, this program decomposes the structures into those individual components using digital topological analysis algorithm. Here is how this is done:
    1. The whole structure is thinned to a one-voxel thick representation of the original structure that maintains the original topology. In this representation, plates become surfaces and rods become curves.
    2. The overall connected surfaces are further thinned along one of the remaining two dimensions to get plate-curves.
    3. Curves for rods and plate-curves for plates are decomposed into individual components using digital topological analysis algorithm.
    4. The original structure is restored with individual components labeled.
