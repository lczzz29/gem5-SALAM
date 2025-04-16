import argparse
import os

def generate_dialect_files(output_dir, dialects_operations):
    for dialect, operations in dialects_operations.items():
        hh_file = os.path.join(output_dir, f"{dialect}.hh")
        cc_file = os.path.join(output_dir, f"{dialect}.cc")

        # Generate .hh file
        with open(hh_file, 'w') as f:
            f.write(f"#ifndef __HWACC_MLIR_{dialect.upper()}_HH__\n")
            f.write(f"#define __HWACC_MLIR_{dialect.upper()}_HH__\n")
            f.write(f"\n")
            f.write("#include \"../operation.hh\"\n")
            f.write("#include \"../irmap.hh\"\n")
            f.write(f"namespace MULA {{\n\n")
            f.write(f"namespace {dialect} {{\n\n")
            for op in operations:
                op_upper = op.upper()
                f.write(f"// MULA-{dialect.upper()}-{op_upper} // -------------------------------------------------------------//\n")
                f.write(f"class {op}Op : public Operation\n")
                f.write("{\n")
                f.write("    private:\n")
                f.write("        std::vector< std::vector<uint64_t> > conditions;\n")
                f.write("        MULA::Debugger *dbgr;\n")
                f.write("        uint64_t currentCycle;\n\n")
                f.write("    protected:\n")
                f.write("    public:\n")
                f.write(f"        {op}Op(uint64_t id, gem5::SimObject * owner, bool dbg,\n")
                f.write("              uint64_t OpCode,\n")
                f.write("              uint64_t cycles,\n")
                f.write("              uint64_t fu);\n")
                f.write(f"        ~{op}Op() = default;\n")
                f.write("        void initialize(mlir::Operation *op,\n")
                f.write("                        MULA::IRMap *irMap\n")
                f.write("                        ) override;\n")
                f.write(f"        uint64_t getCycleCount() {{ return conditions.at(0).at(2); }}\n")
                f.write("        void compute();\n")
                f.write(f"        void dump() {{ if (dbgr->enabled()) {{ dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}}}\n")
                f.write("        void dumper();\n")
                f.write(f"        std::shared_ptr<MULA::{dialect}::{op}Op> clone() const {{ return std::static_pointer_cast<MULA::{dialect}::{op}Op>(createClone()); }}\n")
                f.write(f"        virtual std::shared_ptr<MULA::Operation> createClone() const override {{ return std::shared_ptr<MULA::Operation>(new MULA::{dialect}::{op}Op(*this)); }}\n")
                f.write("};\n\n")
                f.write(f"std::shared_ptr<MULA::Operation>\n")
                f.write(f"create{op}Op(uint64_t id, gem5::SimObject * owner, bool dbg,\n")
                f.write("              uint64_t OpCode,\n")
                f.write("              uint64_t cycles,\n")
                f.write("              uint64_t fu);\n\n")
            f.write(f"}} // namespace {dialect}\n\n")
            f.write(f"}} // namespace MULA\n")
            f.write(f"#endif // __HWACC_MLIR_{dialect.upper()}_HH__\n")
        # Generate .cc file
        with open(cc_file, 'w') as f:
            f.write(f'#include "{dialect}.hh"\n\n')
            f.write(f"namespace MULA {{\n\n")
            f.write(f"namespace {dialect} {{\n\n")
            for op in operations:
                f.write(f"{op}Op::{op}Op(uint64_t id, gem5::SimObject * owner, bool dbg,\n")
                f.write("              uint64_t OpCode,\n")
                f.write("              uint64_t cycles,\n")
                f.write("              uint64_t fu)\n")
                f.write("    : Operation(id, owner, dbg, OpCode, cycles, fu)\n")
                f.write("{\n")
                f.write("    std::vector<uint64_t> base_params;\n")
                f.write("    base_params.push_back(id);\n")
                f.write("    base_params.push_back(OpCode);\n")
                f.write("    base_params.push_back(cycles);\n")
                f.write("    conditions.push_back(base_params);\n")
                f.write("}\n\n")
                f.write(f"void {op}Op::initialize(mlir::Operation *op, MULA::IRMap *irmap)\n")
                f.write("{\n")
                f.write("    MULA::Operation::initialize(op, irmap);\n")
                f.write("}\n\n")
                f.write(f"void {op}Op::compute()\n")
                f.write("{\n")
                f.write("    // Compute code\n")
                f.write("}\n\n")
                f.write(f"void {op}Op::dumper()\n")
                f.write("{\n")
                f.write("    // Dump code\n")
                f.write("}\n\n")
                f.write(f"std::shared_ptr<MULA::Operation>\n")
                f.write(f"create{op}Op(uint64_t id, gem5::SimObject * owner, bool dbg,\n")
                f.write("              uint64_t OpCode,\n")
                f.write("              uint64_t cycles,\n")
                f.write("              uint64_t fu)\n")
                f.write("{\n")
                f.write(f"    return std::make_shared<MULA::{dialect}::{op}Op>(id, owner, dbg, OpCode, cycles, fu);\n")
                f.write("}\n\n")
            f.write(f"}} // namespace {dialect}\n\n")
            f.write(f"}} // namespace MULA\n")

def main():
    parser = argparse.ArgumentParser(description='Generate C++ dialect files.')
    parser.add_argument('output_dir', type=str, help='Path to the output directory')
    args = parser.parse_args()

    if not os.path.exists(args.output_dir):
        os.makedirs(args.output_dir)

    # Define dialects and their operations
    dialects_operations = {
        'arith': [
            'AddF',
            'AddI',
            'AddUIExtended',
            'AndI',
            'Bitcast',
            'CeilDivSI',
            'CeilDivUI',
            'CmpF',
            'CmpI',
            'Constant',
            'DivF',
            'DivSI',
            'DivUI',
            'ExtF',
            'ExtSI',
            'ExtUI',
            'FloorDivSI',
            'FPToSI',
            'FPToUI',
            'IndexCast',
            'IndexCastUI',
            'MaximumF',
            'MaxNumF',
            'MaxSI',
            'MaxUI',
            'MinimumF',
            'MinNumF',
            'MinSI',
            'MinUI',
            'MulF',
            'MulI',
            'MulSIExtended',
            'MulUIExtended',
            'NegF',
            'OrI',
            'RemF',
            'RemSI',
            'RemUI',
            'Select',
            'ShLI',
            'ShRSI',
            'ShRUI',
            'SIToFP',
            'SubF',
            'SubI',
            'TruncF',
            'TruncI',
            'UIToFP',
            'XOrI'
        ],
        'func': [
            'CallIndirect',
            'Call',
            'Constant',
            'Func',
            'Return'
        ],
        'memref': [
            'AssumeAlignment',
            'AtomicRMW',
            'AtomicYield',
            'Copy',
            'GenericAtomicRMW',
            'Load',
            'Alloc',
            'Alloca',
            'AllocaScope',
            'AllocaScopeReturn',
            'Cast',
            'CollapseShape',
            'Dealloc',
            'Dim',
            'DmaStart',
            'DmaWait',
            'ExpandShape',
            'ExtractAlignedPointerAsIndex',
            'ExtractStridedMetadata',
            'GetGlobal',
            'Global',
            'MemorySpaceCast',
            'Prefetch',
            'Rank',
            'Realloc',
            'ReinterpretCast',
            'Reshape',
            'Store',
            'Transpose',
            'View',
            'SubView'
        ],
        'scf': [
            'Condition',
            'ExecuteRegion',
            'For',
            'Forall',
            'InParallel',
            'If',
            'IndexSwitch',
            'Parallel',
            'Reduce',
            'ReduceReturn',
            'While',
            'Yield'
        ],
        'builtin': ['Module']
    }

    generate_dialect_files(args.output_dir, dialects_operations)

if __name__ == '__main__':
    main()