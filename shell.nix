let pkgs = import <nixpkgs> { };
in pkgs.mkShell {
  name = "fGen";
  buildInputs = with pkgs; [ platformio clang-tools ];
}
