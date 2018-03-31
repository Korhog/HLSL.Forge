
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL
{
    using Elements.Base;
    using HLSL.Values;

    public interface IHLSLEditorNode
    {
        HLSLResult GetNodeValue(Node sender);
    }
}
