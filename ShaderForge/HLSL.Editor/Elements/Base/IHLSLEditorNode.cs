
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL
{
    using Elements.Base;

    public interface IHLSLEditorNode
    {
        string GetNodeValue(Node sender);
    }

}
