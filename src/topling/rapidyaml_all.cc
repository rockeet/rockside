#include <rocksdb/slice.h>

#ifdef SIDE_PLUGIN_WITH_YAML
#include <c4/std/string.hpp>
#include <ryml.hpp>

#include <ext/c4core/src/c4/base64.cpp>
#include <ext/c4core/src/c4/char_traits.cpp>
#include <ext/c4core/src/c4/error.cpp>
#include <ext/c4core/src/c4/format.cpp>
#include <ext/c4core/src/c4/language.cpp>
#include <ext/c4core/src/c4/memory_resource.cpp>
#include <ext/c4core/src/c4/memory_util.cpp>
#include <ext/c4core/src/c4/time.cpp>
#include <src/c4/yml/common.cpp>
#include <src/c4/yml/parse.cpp>
#include <src/c4/yml/preprocess.cpp>
#include <src/c4/yml/tree.cpp>

namespace ROCKSDB_NAMESPACE {
std::string YamlToJson(std::string& yaml_str) {
  ryml::Tree yt = ryml::parse(c4::to_substr(yaml_str));
  std::string jstr;
  jstr.reserve(yaml_str.size() * 2);
  ryml::emitrs_json(yt, &jstr);
  return jstr;
}
} // namespace ROCKSDB_NAMESPACE

#else // SIDE_PLUGIN_WITH_YAML

#include <stdexcept>

namespace ROCKSDB_NAMESPACE {
std::string YamlToJson(std::string& yaml_str) {
    throw std::invalid_argument(rocksdb::Slice(ROCKSDB_FUNC) +
        ": yaml is not compiled: SIDE_PLUGIN_WITH_YAML is not defined");
}
} // namespace ROCKSDB_NAMESPACE

#endif // SIDE_PLUGIN_WITH_YAML
