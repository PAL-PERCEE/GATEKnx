FILE(REMOVE_RECURSE
  "../srv_gen"
  "../src/knx_service/srv"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/knx_service/srv/__init__.py"
  "../src/knx_service/srv/_KnxSet.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
