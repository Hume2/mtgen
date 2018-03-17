# Shape

Shape is an enumeration of multi-dimensional shapes used in this project.

## Cube

```SHAPE_CUBE``` is an axis-aligned cube that ranges from the minimum coordinates to the maximum coordinates. All coordinates are indepenndent.

## Orthoplex

```SHAPE_ORTHOPLEX``` is an axis-aligned orthoplex that is dual to the axis-alighned cube. The coordinates also vary from the minimum to the maximum, but there might be only one extreme coordinate in one vector. The orthoplex is D! times smaller than the cube where D is the count of dimensions.

## Simplex

```SHAPE_SIMPLEX``` is not implemented correctly yet. The idea is that N points form a (N-1)-dimensional simplex. Its volume is about D! times smaller where D is the count of dimensions.
