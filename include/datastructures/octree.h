#pragma once
#ifndef OCTREE_H
#define OCTREE_H

struct OctreePoint
{
    real position[3];
    void *data;
};

struct Octree
{
    real origin[3];
    real half_dimension[3];
    struct Octree *children[8];
    struct OctreePoint *point;
};

static inline void octree_init(struct Octree *octree, real origin[3], real half_dimension[3])
{
    for (int child_num = 0; child_num < 8; child_num++)
        octree->children[child_num] = NULL;

    memcpy(octree->origin, origin, sizeof(real) * 3);
    memcpy(octree->half_dimension, half_dimension, sizeof(real) * 3);
}

static inline void octree_delete(struct Octree *octree)
{
    //for (int child_num = 0; child_num < 8; child_num++)
    //{
    //    if (octree->children[child_num] != NULL)
    //        octree_delete(octree->children[child_num]);
    //}

    //free(octree);
}

static inline size_t octree_get_octant_containing_point(struct Octree *octree, real position[3])
{
    size_t oct_num = 0;

    if (position[0] >= octree->origin[0])
        oct_num |= 4;
    if (position[1] >= octree->origin[0])
        oct_num |= 2;
    if (position[2] >= octree->origin[0])
        oct_num |= 1;

    return oct_num;
}

static inline int octree_is_leaf_node(struct Octree *octree)
{
    return octree->children[0] == NULL;
}

static inline void octree_insert(struct Octree *octree, struct OctreePoint *point)
{
    if (octree_is_leaf_node(octree))
    {
        if (octree_is_leaf_node(octree))
        {
            if (octree->point == NULL)
            {
                octree->point = point;
                return;
            }
            else
            {
                struct OctreePoint *old_point = octree->point;
                octree->point = NULL;

                for (int child_num = 0; child_num < 8; child_num++)
                {
                    real new_origin[3];
                    memcpy(new_origin, octree->origin, sizeof(real) * 3);

                    new_origin[0] += octree->half_dimension[0] * (child_num & 4 ? 0.5f : -0.5f);
                    new_origin[1] += octree->half_dimension[1] * (child_num & 2 ? 0.5f : -0.5f);
                    new_origin[2] += octree->half_dimension[2] * (child_num & 1 ? 0.5f : -0.5f);

                    real new_half_dimension[3];
                    memcpy(new_half_dimension, octree->half_dimension, sizeof(real) * 3);
                    new_half_dimension[0] *= 0.5f;
                    new_half_dimension[1] *= 0.5f;
                    new_half_dimension[2] *= 0.5f;

                    octree_init(octree->children[child_num], new_origin, new_half_dimension);
                }

                octree_insert(octree->children[octree_get_octant_containing_point(octree, old_point->position)], old_point);
                octree_insert(octree->children[octree_get_octant_containing_point(octree, point->position)], point);
            }
        }
        else
        {
            size_t octant = octree_get_octant_containing_point(octree, point->position);
            octree_insert(octree->children[octant], point);
        }
    }
}

static inline void octree_get_point_inside_box(struct Octree *octree, real min[3], real max[3], struct Vector *results)
{
    if (octree_is_leaf_node(octree))
    {
        if (octree->point != NULL)
        {
            if (octree->point->position[0] > max[0] || octree->point->position[1] > max[1] || octree->point->position[2] > max[2])
                return;
            if (octree->point->position[0] < min[0] || octree->point->position[1] < min[1] || octree->point->position[2] < min[2])
                return;

            vector_push_back(results, octree->point);
        }
    }
    else
    {
        for (int child_num = 0; child_num < 8; child_num++)
        {
            if (octree->children[child_num]->origin[0] + octree->children[child_num]->half_dimension[0] < min[0] || octree->children[child_num]->origin[0] + octree->children[child_num]->half_dimension[1] < min[1] || octree->children[child_num]->origin[2] + octree->children[child_num]->half_dimension[2] < min[2])
                continue;
            if (octree->children[child_num]->origin[0] - octree->children[child_num]->half_dimension[0] > max[0] || octree->children[child_num]->origin[0] - octree->children[child_num]->half_dimension[1] > max[1] || octree->children[child_num]->origin[2] - octree->children[child_num]->half_dimension[2] > max[2])
                continue;

            octree_get_point_inside_box(octree->children[child_num], min, max, results);
        }
    }
}

#endif
