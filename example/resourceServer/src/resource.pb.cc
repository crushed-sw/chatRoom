// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: resource.proto

#include "../include/resource.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_resource_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ResourceResultCode_resource_2eproto;
namespace crushed {
class ResourceResultCodeDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ResourceResultCode> _instance;
} _ResourceResultCode_default_instance_;
class ResourceRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ResourceRequest> _instance;
} _ResourceRequest_default_instance_;
class ResourceResponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ResourceResponse> _instance;
} _ResourceResponse_default_instance_;
}  // namespace crushed
static void InitDefaultsscc_info_ResourceRequest_resource_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::crushed::_ResourceRequest_default_instance_;
    new (ptr) ::crushed::ResourceRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::crushed::ResourceRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ResourceRequest_resource_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_ResourceRequest_resource_2eproto}, {}};

static void InitDefaultsscc_info_ResourceResponse_resource_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::crushed::_ResourceResponse_default_instance_;
    new (ptr) ::crushed::ResourceResponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::crushed::ResourceResponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_ResourceResponse_resource_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_ResourceResponse_resource_2eproto}, {
      &scc_info_ResourceResultCode_resource_2eproto.base,}};

static void InitDefaultsscc_info_ResourceResultCode_resource_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::crushed::_ResourceResultCode_default_instance_;
    new (ptr) ::crushed::ResourceResultCode();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::crushed::ResourceResultCode::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ResourceResultCode_resource_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_ResourceResultCode_resource_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_resource_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_resource_2eproto = nullptr;
static const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* file_level_service_descriptors_resource_2eproto[1];

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_resource_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceResultCode, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceResultCode, code_),
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceResultCode, type_),
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceResultCode, msg_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceRequest, path_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceResponse, result_),
  PROTOBUF_FIELD_OFFSET(::crushed::ResourceResponse, responsemessage_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::crushed::ResourceResultCode)},
  { 8, -1, sizeof(::crushed::ResourceRequest)},
  { 14, -1, sizeof(::crushed::ResourceResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::crushed::_ResourceResultCode_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::crushed::_ResourceRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::crushed::_ResourceResponse_default_instance_),
};

const char descriptor_table_protodef_resource_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016resource.proto\022\007crushed\"=\n\022ResourceRes"
  "ultCode\022\014\n\004code\030\001 \001(\005\022\014\n\004type\030\002 \001(\014\022\013\n\003m"
  "sg\030\003 \001(\014\"\037\n\017ResourceRequest\022\014\n\004path\030\001 \001("
  "\014\"X\n\020ResourceResponse\022+\n\006result\030\001 \001(\0132\033."
  "crushed.ResourceResultCode\022\027\n\017responseMe"
  "ssage\030\002 \001(\0142U\n\017ResourceService\022B\n\013getRes"
  "ource\022\030.crushed.ResourceRequest\032\031.crushe"
  "d.ResourceResponseB\003\200\001\001b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_resource_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_resource_2eproto_sccs[3] = {
  &scc_info_ResourceRequest_resource_2eproto.base,
  &scc_info_ResourceResponse_resource_2eproto.base,
  &scc_info_ResourceResultCode_resource_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_resource_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_resource_2eproto = {
  false, false, descriptor_table_protodef_resource_2eproto, "resource.proto", 311,
  &descriptor_table_resource_2eproto_once, descriptor_table_resource_2eproto_sccs, descriptor_table_resource_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_resource_2eproto::offsets,
  file_level_metadata_resource_2eproto, 3, file_level_enum_descriptors_resource_2eproto, file_level_service_descriptors_resource_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_resource_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_resource_2eproto)), true);
namespace crushed {

// ===================================================================

void ResourceResultCode::InitAsDefaultInstance() {
}
class ResourceResultCode::_Internal {
 public:
};

ResourceResultCode::ResourceResultCode(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:crushed.ResourceResultCode)
}
ResourceResultCode::ResourceResultCode(const ResourceResultCode& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_type().empty()) {
    type_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_type(),
      GetArena());
  }
  msg_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_msg().empty()) {
    msg_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_msg(),
      GetArena());
  }
  code_ = from.code_;
  // @@protoc_insertion_point(copy_constructor:crushed.ResourceResultCode)
}

void ResourceResultCode::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ResourceResultCode_resource_2eproto.base);
  type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  msg_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  code_ = 0;
}

ResourceResultCode::~ResourceResultCode() {
  // @@protoc_insertion_point(destructor:crushed.ResourceResultCode)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void ResourceResultCode::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  type_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  msg_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ResourceResultCode::ArenaDtor(void* object) {
  ResourceResultCode* _this = reinterpret_cast< ResourceResultCode* >(object);
  (void)_this;
}
void ResourceResultCode::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ResourceResultCode::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ResourceResultCode& ResourceResultCode::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ResourceResultCode_resource_2eproto.base);
  return *internal_default_instance();
}


void ResourceResultCode::Clear() {
// @@protoc_insertion_point(message_clear_start:crushed.ResourceResultCode)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  type_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  msg_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  code_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ResourceResultCode::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          code_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_type();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes msg = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_msg();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ResourceResultCode::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:crushed.ResourceResultCode)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 code = 1;
  if (this->code() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_code(), target);
  }

  // bytes type = 2;
  if (this->type().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_type(), target);
  }

  // bytes msg = 3;
  if (this->msg().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        3, this->_internal_msg(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:crushed.ResourceResultCode)
  return target;
}

size_t ResourceResultCode::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:crushed.ResourceResultCode)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes type = 2;
  if (this->type().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_type());
  }

  // bytes msg = 3;
  if (this->msg().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_msg());
  }

  // int32 code = 1;
  if (this->code() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_code());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ResourceResultCode::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:crushed.ResourceResultCode)
  GOOGLE_DCHECK_NE(&from, this);
  const ResourceResultCode* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ResourceResultCode>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:crushed.ResourceResultCode)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:crushed.ResourceResultCode)
    MergeFrom(*source);
  }
}

void ResourceResultCode::MergeFrom(const ResourceResultCode& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:crushed.ResourceResultCode)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.type().size() > 0) {
    _internal_set_type(from._internal_type());
  }
  if (from.msg().size() > 0) {
    _internal_set_msg(from._internal_msg());
  }
  if (from.code() != 0) {
    _internal_set_code(from._internal_code());
  }
}

void ResourceResultCode::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:crushed.ResourceResultCode)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResourceResultCode::CopyFrom(const ResourceResultCode& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:crushed.ResourceResultCode)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResourceResultCode::IsInitialized() const {
  return true;
}

void ResourceResultCode::InternalSwap(ResourceResultCode* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  type_.Swap(&other->type_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  msg_.Swap(&other->msg_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(code_, other->code_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ResourceResultCode::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void ResourceRequest::InitAsDefaultInstance() {
}
class ResourceRequest::_Internal {
 public:
};

ResourceRequest::ResourceRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:crushed.ResourceRequest)
}
ResourceRequest::ResourceRequest(const ResourceRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  path_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_path().empty()) {
    path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_path(),
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:crushed.ResourceRequest)
}

void ResourceRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ResourceRequest_resource_2eproto.base);
  path_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

ResourceRequest::~ResourceRequest() {
  // @@protoc_insertion_point(destructor:crushed.ResourceRequest)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void ResourceRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  path_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ResourceRequest::ArenaDtor(void* object) {
  ResourceRequest* _this = reinterpret_cast< ResourceRequest* >(object);
  (void)_this;
}
void ResourceRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ResourceRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ResourceRequest& ResourceRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ResourceRequest_resource_2eproto.base);
  return *internal_default_instance();
}


void ResourceRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:crushed.ResourceRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  path_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ResourceRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // bytes path = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_path();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ResourceRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:crushed.ResourceRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes path = 1;
  if (this->path().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_path(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:crushed.ResourceRequest)
  return target;
}

size_t ResourceRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:crushed.ResourceRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes path = 1;
  if (this->path().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_path());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ResourceRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:crushed.ResourceRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const ResourceRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ResourceRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:crushed.ResourceRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:crushed.ResourceRequest)
    MergeFrom(*source);
  }
}

void ResourceRequest::MergeFrom(const ResourceRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:crushed.ResourceRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.path().size() > 0) {
    _internal_set_path(from._internal_path());
  }
}

void ResourceRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:crushed.ResourceRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResourceRequest::CopyFrom(const ResourceRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:crushed.ResourceRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResourceRequest::IsInitialized() const {
  return true;
}

void ResourceRequest::InternalSwap(ResourceRequest* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  path_.Swap(&other->path_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata ResourceRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void ResourceResponse::InitAsDefaultInstance() {
  ::crushed::_ResourceResponse_default_instance_._instance.get_mutable()->result_ = const_cast< ::crushed::ResourceResultCode*>(
      ::crushed::ResourceResultCode::internal_default_instance());
}
class ResourceResponse::_Internal {
 public:
  static const ::crushed::ResourceResultCode& result(const ResourceResponse* msg);
};

const ::crushed::ResourceResultCode&
ResourceResponse::_Internal::result(const ResourceResponse* msg) {
  return *msg->result_;
}
ResourceResponse::ResourceResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:crushed.ResourceResponse)
}
ResourceResponse::ResourceResponse(const ResourceResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  responsemessage_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_responsemessage().empty()) {
    responsemessage_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_responsemessage(),
      GetArena());
  }
  if (from._internal_has_result()) {
    result_ = new ::crushed::ResourceResultCode(*from.result_);
  } else {
    result_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:crushed.ResourceResponse)
}

void ResourceResponse::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ResourceResponse_resource_2eproto.base);
  responsemessage_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  result_ = nullptr;
}

ResourceResponse::~ResourceResponse() {
  // @@protoc_insertion_point(destructor:crushed.ResourceResponse)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void ResourceResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  responsemessage_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete result_;
}

void ResourceResponse::ArenaDtor(void* object) {
  ResourceResponse* _this = reinterpret_cast< ResourceResponse* >(object);
  (void)_this;
}
void ResourceResponse::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ResourceResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ResourceResponse& ResourceResponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ResourceResponse_resource_2eproto.base);
  return *internal_default_instance();
}


void ResourceResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:crushed.ResourceResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  responsemessage_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  if (GetArena() == nullptr && result_ != nullptr) {
    delete result_;
  }
  result_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ResourceResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .crushed.ResourceResultCode result = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_result(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes responseMessage = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_responsemessage();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ResourceResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:crushed.ResourceResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .crushed.ResourceResultCode result = 1;
  if (this->has_result()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::result(this), target, stream);
  }

  // bytes responseMessage = 2;
  if (this->responsemessage().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_responsemessage(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:crushed.ResourceResponse)
  return target;
}

size_t ResourceResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:crushed.ResourceResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes responseMessage = 2;
  if (this->responsemessage().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_responsemessage());
  }

  // .crushed.ResourceResultCode result = 1;
  if (this->has_result()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *result_);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ResourceResponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:crushed.ResourceResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const ResourceResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ResourceResponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:crushed.ResourceResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:crushed.ResourceResponse)
    MergeFrom(*source);
  }
}

void ResourceResponse::MergeFrom(const ResourceResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:crushed.ResourceResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.responsemessage().size() > 0) {
    _internal_set_responsemessage(from._internal_responsemessage());
  }
  if (from.has_result()) {
    _internal_mutable_result()->::crushed::ResourceResultCode::MergeFrom(from._internal_result());
  }
}

void ResourceResponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:crushed.ResourceResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResourceResponse::CopyFrom(const ResourceResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:crushed.ResourceResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResourceResponse::IsInitialized() const {
  return true;
}

void ResourceResponse::InternalSwap(ResourceResponse* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  responsemessage_.Swap(&other->responsemessage_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(result_, other->result_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ResourceResponse::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

ResourceService::~ResourceService() {}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* ResourceService::descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_resource_2eproto);
  return file_level_service_descriptors_resource_2eproto[0];
}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* ResourceService::GetDescriptor() {
  return descriptor();
}

void ResourceService::getResource(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                         const ::crushed::ResourceRequest*,
                         ::crushed::ResourceResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method getResource() not implemented.");
  done->Run();
}

void ResourceService::CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                             ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                             const ::PROTOBUF_NAMESPACE_ID::Message* request,
                             ::PROTOBUF_NAMESPACE_ID::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), file_level_service_descriptors_resource_2eproto[0]);
  switch(method->index()) {
    case 0:
      getResource(controller,
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ::crushed::ResourceRequest*>(
                 request),
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<::crushed::ResourceResponse*>(
                 response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message& ResourceService::GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::crushed::ResourceRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
          ->GetPrototype(method->input_type());
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message& ResourceService::GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::crushed::ResourceResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
          ->GetPrototype(method->output_type());
  }
}

ResourceService_Stub::ResourceService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
ResourceService_Stub::ResourceService_Stub(
    ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
    ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::PROTOBUF_NAMESPACE_ID::Service::STUB_OWNS_CHANNEL) {}
ResourceService_Stub::~ResourceService_Stub() {
  if (owns_channel_) delete channel_;
}

void ResourceService_Stub::getResource(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                              const ::crushed::ResourceRequest* request,
                              ::crushed::ResourceResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace crushed
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::crushed::ResourceResultCode* Arena::CreateMaybeMessage< ::crushed::ResourceResultCode >(Arena* arena) {
  return Arena::CreateMessageInternal< ::crushed::ResourceResultCode >(arena);
}
template<> PROTOBUF_NOINLINE ::crushed::ResourceRequest* Arena::CreateMaybeMessage< ::crushed::ResourceRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::crushed::ResourceRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::crushed::ResourceResponse* Arena::CreateMaybeMessage< ::crushed::ResourceResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::crushed::ResourceResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
