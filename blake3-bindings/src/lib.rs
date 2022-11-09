struct Hash;

#[no_mangle]
pub extern "C" fn hash(data: *const u8, length: usize) -> *mut blake3::Hash {
    unsafe {
        let input = std::slice::from_raw_parts(data, length);
        Box::into_raw(Box::new(blake3::hash(input)))
    }
}

#[no_mangle]
pub extern "C" fn add(left: usize, right: usize) -> usize {
    left + right
}
