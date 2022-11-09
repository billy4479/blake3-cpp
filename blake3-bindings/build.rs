use std::env;

fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    let out_file = format!("{}/blake3.h", std::env::var("BUILD_DIR").unwrap_or(String::from(".")));


    cbindgen::Builder::new()
      .with_crate(crate_dir)
      .generate()
      .expect("Unable to generate bindings")
      .write_to_file(out_file);
}