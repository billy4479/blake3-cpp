use std::alloc::{dealloc, Layout};
use std::ffi::{c_char, c_ulonglong, CString};
use std::ptr;

// We need these to generate a opaque struct in the header
#[allow(dead_code)]
struct Hash;
#[allow(dead_code)]
struct Hasher;

#[no_mangle]
pub extern "C" fn hash(data: *const u8, length: usize) -> *mut blake3::Hash {
    unsafe {
        let input = std::slice::from_raw_parts(data, length);
        Box::into_raw(Box::new(blake3::hash(input)))
    }
}

#[no_mangle]
pub extern "C" fn free_hash(hash: *mut blake3::Hash) {
    unsafe {
        ptr::drop_in_place(hash);
        dealloc(hash as *mut u8, Layout::new::<blake3::Hash>());
    }
}

#[no_mangle]
pub extern "C" fn hash_as_bytes(hash: *const blake3::Hash) -> &'static [u8; 32] {
    unsafe { hash.as_ref().unwrap().as_bytes() }
}

#[no_mangle]
pub extern "C" fn hash_as_hex(hash: *const blake3::Hash) -> *const c_char {
    unsafe {
        let s = CString::new(hash.as_ref().unwrap().to_hex().as_str()).unwrap();
        let ptr = s.as_ptr();

        std::mem::forget(s);
        ptr
    }
}

#[no_mangle]
pub extern "C" fn new_hasher() -> *mut blake3::Hasher {
    Box::into_raw(Box::new(blake3::Hasher::new()))
}

#[no_mangle]
pub extern "C" fn free_hasher(hasher: *mut blake3::Hasher) {
    unsafe {
        ptr::drop_in_place(hasher);
        dealloc(hasher as *mut u8, Layout::new::<blake3::Hasher>());
    }
}

#[no_mangle]
pub extern "C" fn hasher_update(hasher: *mut blake3::Hasher, data: *const u8, length: usize) {
    unsafe {
        let input = std::slice::from_raw_parts(data, length);
        hasher.as_mut().unwrap().update(input);
    }
}

#[no_mangle]
pub extern "C" fn hasher_update_rayon(hasher: *mut blake3::Hasher, data: *const u8, length: usize) {
    unsafe {
        let input = std::slice::from_raw_parts(data, length);
        hasher.as_mut().unwrap().update_rayon(input);
    }
}

#[no_mangle]
pub extern "C" fn hasher_finalize(hasher: *mut blake3::Hasher) -> *mut blake3::Hash {
    unsafe { Box::into_raw(Box::new(hasher.as_mut().unwrap().finalize())) }
}

#[no_mangle]
pub extern "C" fn hasher_reset(hasher: *mut blake3::Hasher) {
    unsafe {
        hasher.as_mut().unwrap().reset();
    }
}

#[no_mangle]
pub extern "C" fn hasher_count(hasher: *mut blake3::Hasher) -> c_ulonglong {
    unsafe { hasher.as_mut().unwrap().count() }
}

// TODO: new_keyed and new_derive_key
