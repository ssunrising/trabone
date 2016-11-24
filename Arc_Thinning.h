int Is_sopen_surface_pt(int ***matrix, int i, int j, int k, int thr);
int Is_eopen_surface_pt(int ***matrix, int i, int j, int k, int thr);
int Is_vopen_surface_pt(int ***matrix, int i, int j, int k, int thr);
int Arc_Shape_Point(int ***matrix, int i, int j, int k, int thr); /*return 1 when it's a shape point, return 0 when it's not a shape pt*/
int Arc_Erodable_Point(int ***matrix, int i, int j, int k); /*return 1 when it's an arc shape point, return 0 when it's not a shape pt*/
