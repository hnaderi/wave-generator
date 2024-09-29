let pkgs = import <nixpkgs> { };
in pkgs.mkShell {
  name = "waveform-generator";
  buildInputs = with pkgs; [ platformio clang-tools ];
}
