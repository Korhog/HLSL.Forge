using System;
using System.Linq;
using System.Reflection;
using rMind.CanvasEx;

namespace HLSL.Editor.Elements.Base
{
    public class HLSLNodeController : rMind.Elements.rMindBaseController
    {
        public HLSLNodeController(rMindCanvasController parent) : base(parent)
        {

        }

        public void CreateItem(Type type)
        {
            var assembly = Assembly.GetExecutingAssembly();
            var item = assembly.ExportedTypes.Where(x => x == type).FirstOrDefault();
            if (item == null)
                return;

            try
            {
                var instance = (rMind.Elements.rMindBaseElement)Activator.CreateInstance(item, this);
                if (instance == null)
                    return;

                instance.Translate(new rMind.Types.Vector2(200, 200));
                AddElement(instance);
            }
            finally { /* Ignore */ }   
        }
    }
}
