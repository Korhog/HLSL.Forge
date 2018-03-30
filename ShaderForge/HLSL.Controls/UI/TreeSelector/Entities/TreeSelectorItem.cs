using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Controls
{
    public class TreeSelectorItem : ITreeSelectorItem
    {
        public Type Type { get; set; }

        public string Name { get; set; }
        public string SemanticName { get; set; }

        public bool Folder => false;

        public ITreeSelectorItem Parent { get; set; }

        public ObservableCollection<ITreeSelectorItem> Children => null;
    }
}
